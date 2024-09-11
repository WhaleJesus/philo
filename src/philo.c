/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:09:25 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/11 18:31:55 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void	decide_forks(t_data *data)
{
	int	philo_id;
	
	philo_id = data->philo_id;
	if (philo_id == data->n_philo)
	{
		data->nf = &data->forks[0];
		data->ff = &data->forks[philo_id - 1];
	}
	else if (data->philo_id % 2 == 0)
	{
		data->nf = &data->forks[philo_id];
		data->ff = &data->forks[philo_id - 1];
	}
	else
	{
		data->ff = &data->forks[philo_id];
		data->nf = &data->forks[philo_id - 1];
	}
}

int	print_msg(char *msg, t_data *data, unsigned long time, int deadmsg)
{
	if (!(*(data->dead) == 0) || deadmsg == 1)
	{
		pthread_mutex_lock(data->print);
		if (!(*(data->dead) == 0)
				|| (deadmsg == 1 && !(*(data->dead) == 0)))
		{
			time = get_timediff(data->start);
			printf("%lu %i %s\n", time, data->philo_id, msg);
			if (deadmsg == 1)
				*(data->dead) = 0;
		}
		else
		{
			pthread_mutex_unlock(data->print);
			return (-1);
		}
		pthread_mutex_unlock(data->print);
		return (1);
	}
	else
		return (-1);
}

int	check_dead(t_data *data, int ct)
{
	unsigned long	time_die;

	time_die = (unsigned long)data->time_die;
	if (get_timediff(data->time_since_eat) > time_die)
	{
		print_msg("died", data, ct, 1);
		return (-1);
	}
	return (1);
}

int	while_loopje(unsigned long st, int time, t_data *data, unsigned long ct)
{
	while (get_timediff(st) < (unsigned long)time)
	{
		if (check_dead(data, ct) == -1)
			return (-1);
		usleep(100);
	}
	return (1);
}

int	philo_eat(t_data *data)
{
	unsigned long	st;
	unsigned long	ct;

	ct = get_timediff(data->start);
	pthread_mutex_lock(data->ff);
	if (print_msg("has taken a fork", data, ct, 0) == -1)
		return (-1);
	if (check_dead(data, ct) == -1)
		return (-1);
	pthread_mutex_lock(data->nf);
	ct = get_timediff(data->start);
	if (print_msg("is eating", data, ct, 0) == -1)
		return (-1);
	st = get_time();
	data->time_since_eat = st;
	if (while_loopje(st, data->time_eat, data, ct) == -1)
		return (-1);
//	printf("%lu %i done eating\n", get_timediff(st), data->philo_id);
	return (1);
}

int	philo_sleep(t_data *data)
{
	unsigned long	st;
	unsigned long	ct;

	st = get_time();
	ct = get_timediff(data->start);
	if (print_msg("is sleeping", data, ct, 0) == -1)
		return (-1);
	if (while_loopje(st, data->time_sleep, data, ct) == -1)
		return (-1);
	return (1);
}

int	philo_think(t_data *data)
{
	unsigned long	ct;

	ct = get_timediff(data->start);
	if (print_msg("is thinking", data, ct, 0) == -1)
		return (-1);
	return (1);
}

int	philo_cycle(t_data *data)
{
	int	check;

	check = philo_eat(data);
	pthread_mutex_unlock(data->ff);
	pthread_mutex_unlock(data->nf);
	if (check == -1)
		return (-1);
	if (philo_sleep(data) == -1)
		return (-1);
	if (philo_think(data) == -1)
		return (-1);
	return (1);
}

void	one_philo(t_data *data)
{
	unsigned long	ct;

	ct = get_timediff(data->start);
	while (check_dead(data, ct) == 1)
		ct = get_timediff(data->start);
	return ;
}

void	*run_philo(void *ptr)
{
	t_data *data;
	int	check;

	data = (t_data *)ptr;
	decide_forks(data);
	check = 1;
	data->time_since_eat = get_time();
	if (data->n_philo == 1)
		one_philo(data);
	else
	{
		while (check == 1)
			check = philo_cycle(data);
	}
	return ((void *)ptr);
}

void	init_philos(t_data data, pthread_t *phils)
{
	t_data	*data_philo;
	int		i;

	i = 0;
	while (i < data.n_philo)
		pthread_mutex_init(&data.forks[i++], NULL);
	pthread_mutex_init(data.print, NULL);
	data_philo = malloc(sizeof(t_data) * data.n_philo);
	data.start = get_time();
	i = 0;
	while (i < data.n_philo)
	{
		*data_philo = data;
		(*data_philo).philo_id = i + 1;
		pthread_create(&phils[i++], NULL, run_philo, (void *)data_philo++);
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(phils[i], NULL);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
		pthread_mutex_destroy(&data.forks[i++]);
	pthread_mutex_destroy(data.print);
	free_eryting(data_philo, data, phils);
}

void	*init_main(void *ptr)
{
	t_data			data;
	pthread_t		*phils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	int				dead;
	int				ac;
	char			**av;

	av = (char **)ptr;
	ac = array_len(av);
	data.n_philo = ft_atoi(av[1]);
	data.time_die = ft_atoi(av[2]);
	data.time_eat = ft_atoi(av[3]);
	data.time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.max_eat = ft_atoi(av[5]);
	else
		data.max_eat = -1;
	phils = malloc(sizeof(pthread_t) * data.n_philo);
	forks = malloc(sizeof(pthread_mutex_t) * data.n_philo);
	print = malloc(sizeof(pthread_mutex_t));
	dead = 1;
	data.forks = forks;
	data.dead = &dead;
	data.print = print;
	init_philos(data, phils);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	table;

	if (argc < 5 || argc > 6)
		return (0);
	pthread_create(&table, NULL, init_main, (void *)argv);
	pthread_join(table, NULL);
}

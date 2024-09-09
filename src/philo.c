/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:09:25 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/09 17:20:26 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void	*run_philo(void *ptr)
{
	t_data *data;

	data = (t_data *)ptr;
	


	return ((void *)ptr);
}

void	init_philos(t_data data, pthread_t *phils)
{
	t_data	*data_philo;
	int		i;

	i = 0;
	while (i < data.n_philo)
		pthread_mutex_init(&data.forks[i++], NULL);
	data_philo = malloc(sizeof(t_data) * data.n_philo);
	if (!data_philo)
		printf("malloc failed?");
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
	free_eryting(data_philo, data, phils);
}

void	*init_main(void *ptr)
{
	t_data			data;
	pthread_t		*phils;
	pthread_mutex_t	*forks;
	int				dead;
	int				ac;
	char			**av;

	av = (char **)ptr;
	ac = 5;
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
	dead = 1;
	data.forks = forks;
	data.dead = &dead;
	printf("end init main\n");
	init_philos(data, phils);
	printf("wattefuckkk");
	return ((void *)ptr);
}

int	main(int argc, char **argv)
{
	pthread_t	table;

	if (argc < 5 || argc > 6)
		return (0);
	pthread_create(&table, NULL, init_main, (void *)argv);
	pthread_join(table, NULL);
	printf("manbro\n");
}

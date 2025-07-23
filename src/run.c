/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:32:26 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:33:18 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	increment_long(&philo->prog->prog_mtx, &philo->prog->threads_count);
	wait_threads_ready(philo);
	set_long(&philo->philo_mtx, &philo->last_meal, get_time(MICROSECOND));
	desync(philo);
	while (!sim_finished(philo->prog)
		&& !get_bool(&philo->philo_mtx, &philo->full))
	{
		if (philo->full)
			break ;
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	decrement_long(&philo->prog->prog_mtx, &philo->prog->threads_count);
	return (NULL);
}

void	*prog_routine(void *data)
{
	t_program	*prog;

	prog = (t_program *)data;
	program_routine(prog);
	return (NULL);
}

void	*one_philo(void *data)
{
	t_philo	*philo;
	long	start;
	long	time;

	philo = (t_philo *)data;
	start = get_time(MILLISECOND);
	printf("%i %i has taken a fork\n", 0, philo->id);
	usleep(philo->prog->time_die);
	time = get_timediff(start, MILLISECOND);
	printf("%lu %i has died\n", time, philo->id);
	return (NULL);
}

void	launch_threads(t_program *prog)
{
	int	i;

	if (prog->max_meals == 0)
		return ;
	if (prog->n_philos == 1)
	{
		pthread_create(&prog->philos[0]->thread, NULL,
			one_philo, prog->philos[0]);
		pthread_join(prog->philos[0]->thread, NULL);
		return ;
	}
	i = -1;
	while (++i < prog->n_philos)
		pthread_create(&prog->philos[i]->thread,
			NULL, philo_routine, prog->philos[i]);
	pthread_create(&prog->thread, NULL, prog_routine, prog);
	set_long(&prog->prog_mtx, &prog->start, get_time(MILLISECOND));
	set_bool(&prog->prog_mtx, &prog->threads_ready, true);
	i = -1;
	while (++i < prog->n_philos)
		pthread_join(prog->philos[i]->thread, NULL);
	set_bool(&prog->prog_mtx, &prog->end, true);
	pthread_join(prog->thread, NULL);
}

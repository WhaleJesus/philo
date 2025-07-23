/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:29:27 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:30:20 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_msg(t_philo *philo, char *msg, char *color, bool prog)
{
	long	tstamp;
	long	start;

	if ((!sim_finished(philo->prog) || prog) && !philo->full)
	{
		pthread_mutex_lock(&philo->prog->write_lock);
		start = get_long(&philo->prog->prog_mtx, &philo->prog->start);
		tstamp = 0;
		if (start != 0)
			tstamp = get_timediff(start, MILLISECOND);
		printf("%s%lu %i %s%s\n", color, tstamp, philo->id, msg, NC);
		pthread_mutex_unlock(&philo->prog->write_lock);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->ff->fork);
	write_msg(philo, "has taken a fork", YELLOW, false);
	pthread_mutex_lock(&philo->nf->fork);
	write_msg(philo, "has taken a fork", YELLOW, false);
	write_msg(philo, "is eating", GREEN, false);
	set_long(&philo->philo_mtx, &philo->last_meal,
		get_time(MICROSECOND));
	increment_long(&philo->philo_mtx, &philo->n_meals);
	if (philo->n_meals >= philo->max_meals
		&& philo->max_meals != -1)
	{
		set_bool(&philo->philo_mtx, &philo->full, true);
		increment_long(&philo->prog->prog_mtx, &philo->prog->full);
	}
	usleep_on_crack(philo->prog->time_eat, philo->prog);
	pthread_mutex_unlock(&philo->ff->fork);
	pthread_mutex_unlock(&philo->nf->fork);
}

void	philo_sleep(t_philo *philo)
{
	write_msg(philo, "is sleeping", NEON, false);
	usleep_on_crack(philo->prog->time_sleep, philo->prog);
}

void	think(t_philo *philo)
{
	long	think;

	write_msg(philo, "is thinking", NC, false);
	if (philo->prog->n_philos % 2 == 0)
		return ;
	think = philo->prog->time_eat * 2 - philo->prog->time_sleep;
	if (think < 0)
		think = 0;
	usleep_on_crack(think * 0.42, philo->prog);
}

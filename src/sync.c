/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:31:40 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:32:01 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_threads_ready(t_philo *philo)
{
	while (!get_bool(&philo->prog->prog_mtx, &philo->prog->threads_ready))
		;
}

void	desync(t_philo *philo)
{
	if (philo->prog->n_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep_on_crack(philo->prog->time_eat / 3, philo->prog);
	}
	else
	{
		if (philo->id % 2 == 0)
			//usleep_on_crack(3e4, philo->prog);
			usleep_on_crack(philo->prog->time_eat / 3, philo->prog);
	}
}

void	decrement_long(pthread_mutex_t *mtx, long *dest)
{
	pthread_mutex_lock(mtx);
	(*dest)--;
	pthread_mutex_unlock(mtx);
}

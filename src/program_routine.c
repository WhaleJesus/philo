/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:27:30 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:27:53 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	sim_finished(t_program *prog)
{
	bool	b;

	b = get_bool(&prog->prog_mtx, &prog->end);
	return (b);
}

void	program_routine(t_program *prog)
{
	long	i;
	t_philo	*philo;
	long	last_meal;

	while (!sim_finished(prog))
	{
		i = 0;
		while (i < prog->n_philos)
		{
			if (sim_finished(prog))
				break ;
			philo = prog->philos[i];
			if (get_bool(&philo->philo_mtx, &philo->full))
				continue ;
			last_meal = get_long(&philo->philo_mtx, &philo->last_meal);
			if (get_timediff(last_meal, MICROSECOND) > prog->time_die)
			{
				set_bool(&prog->prog_mtx, &prog->end, true);
				write_msg(philo, "has died", RED, true);
				break ;
			}
			i++;
		}
	}
}

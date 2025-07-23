/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:30:42 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:31:24 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	assign_forks(t_program *prog)
{
	int		i;
	int		count;
	t_philo	*philo;

	i = -1;
	while (++i < prog->n_philos)
	{
		philo = prog->philos[i];
		count = philo->prog->n_philos;
		philo->nf = prog->forks[i];
		philo->ff = prog->forks[(i + 1) % count];
		if (philo->id % 2 == 0)
		{
			philo->ff = prog->forks[i];
			philo->nf = prog->forks[(i + 1) % count];
		}
	}
}

t_fork	*init_fork(int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	fork->id = id;
	pthread_mutex_init(&fork->fork, NULL);
	return (fork);
}

t_philo	*init_philo(t_program *prog, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->max_meals = prog->max_meals;
	philo->last_meal = get_time(MICROSECOND);
	philo->n_meals = 0;
	philo->full = false;
	philo->prog = prog;
	return (philo);
}

void	init_program(t_data *data, t_program *prog)
{
	int	i;

	prog->forks = malloc(sizeof(t_fork *) * data->n_philo);
	prog->philos = malloc(sizeof(t_philo *) * data->n_philo);
	prog->n_philos = data->n_philo;
	prog->time_die = data->time_die;
	prog->time_eat = data->time_eat;
	prog->time_sleep = data->time_sleep;
	prog->max_meals = data->max_meals;
	prog->threads_count = 0;
	prog->full = 0;
	prog->start = 0;
	prog->threads_ready = false;
	prog->end = false;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->prog_mtx, NULL);
	i = -1;
	while (++i < prog->n_philos)
	{
		prog->philos[i] = init_philo(prog, i + 1);
		prog->forks[i] = init_fork(i + 1);
	}
	assign_forks(prog);
}

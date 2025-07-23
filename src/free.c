/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:33:55 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:33:56 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_prog(t_program *prog)
{
	int	i;

	i = -1;
	while (++i < prog->n_philos)
		free(prog->forks[i]);
	free(prog->forks);
	i = -1;
	while (++i < prog->n_philos)
		free(prog->philos[i]);
	free(prog->philos);
}

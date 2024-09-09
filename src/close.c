/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:52:36 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/09 17:15:27 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_eryting(t_data *my_data, t_data data, pthread_t *phils)
{
	int	i;

	i = 0;
	while (i < data.n_philo)
	{
		my_data--;
		i++;
	}
	free(my_data);
	free(data.forks);
	free(phils);
}

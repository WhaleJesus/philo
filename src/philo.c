/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:09:25 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/08 15:51:00 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void	init_data(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = -1;
	printf("gay\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	init_data(data, argc, argv);
	printf("%i\n", data->time_die);
}

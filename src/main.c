/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:27:22 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:27:23 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_msg(char *msg, int exitcode)
{
	printf("%s\n", msg);
	exit(exitcode);
}

void	init_data(t_data *data, int ac, char **av)
{
	char	*arg;
	int		i;
	int		j;

	j = 0;
	while (av[++j])
	{
		i = -1;
		arg = av[j];
		while (arg[++i])
		{
			if (arg[i] != 0)
			{
				if (!isdigit(arg[i]))
					exit_msg("Error: arg not a number", 1);
			}
		}
	}
	data->n_philo = atoi(av[1]);
	data->time_die = atoi(av[2]) * 1000;
	data->time_eat = atoi(av[3]) * 1000;
	data->time_sleep = atoi(av[4]) * 1000;
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_program	program;

	if (ac < 5 || ac > 6)
		exit_msg("Args: philo's, time to die, eat, sleep, max meals", 0);
	init_data(&data, ac, av);
	init_program(&data, &program);
	launch_threads(&program);
	destroy_mutexes(&program);
	free_prog(&program);
}

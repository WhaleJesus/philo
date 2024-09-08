/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:23:42 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/08 15:46:47 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct	timeval	t_timeval;
typedef struct	s_data
{
	int					philo_id;
	int					n_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					max_eat;
	unsigned long		start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*ff;
	pthread_mutex_t		*nf;
	bool				*dead;
}	t_data;

unsigned long	get_time();
unsigned long	get_timediff(unsigned long start);
int	ft_atoi(const char *nptr);
#endif

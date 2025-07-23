/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:27:14 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:27:15 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(pthread_mutex_t *mtx, bool *dest, bool value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

bool	get_bool(pthread_mutex_t *mtx, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *value;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

long	get_long(pthread_mutex_t *mtx, long *val)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *val;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	increment_long(pthread_mutex_t *mtx, long *dest)
{
	pthread_mutex_lock(mtx);
	(*dest)++;
	pthread_mutex_unlock(mtx);
}

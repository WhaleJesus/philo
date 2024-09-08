/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:32:52 by sklaps            #+#    #+#             */
/*   Updated: 2024/09/08 15:46:10 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time()
{
	t_timeval	end;

	gettimeofday(&end, 0);
	return ((end.tv_sec * 1000) + (end.tv_usec / 1000));
}

unsigned long	get_timediff(unsigned long start)
{
	unsigned long	end;
	
	end = get_time();
	return (end - start);
}

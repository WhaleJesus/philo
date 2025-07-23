/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:27:00 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:27:02 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(t_timecode timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_msg("Gettimeofday failed", 1);
	if (SECOND == timecode)
		return (tv.tv_usec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == timecode)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == timecode)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (-1);
}

long	get_timediff(long start, t_timecode timecode)
{
	return (get_time(timecode) - start);
}

void	usleep_on_crack(long usec, t_program *prog)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (sim_finished(prog))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

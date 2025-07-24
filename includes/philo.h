/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:34:07 by sklaps            #+#    #+#             */
/*   Updated: 2025/07/23 15:35:14 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>

# define GREEN		"\033[0;32m"
# define YELLOW		"\033[38;2;255;255;0m"
# define NEON		"\033[38;5;198m"
# define RED		"\033[38;2;255;0;0m"
# define NC			"\033[0m"

typedef enum e_timecode
{
	MICROSECOND,
	MILLISECOND,
	SECOND,
}	t_timecode;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long				max_meals;
	long				last_meal;
	long				n_meals;
	bool				full;
	struct s_fork		*ff;
	struct s_fork		*nf;
	pthread_mutex_t		philo_mtx;
	struct s_program	*prog;
}	t_philo;

typedef struct s_program
{
	pthread_t		thread;
	long			n_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			max_meals;
	long			start;
	long			threads_count;
	long			full;
	bool			threads_ready;
	bool			end;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	prog_mtx;
	struct s_fork	**forks;
	struct s_philo	**philos;
}	t_program;

typedef struct s_data
{
	long			n_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			max_meals;
}	t_data;

//main
void	exit_msg(char *msg, int exitcode);

//init_philo
void	init_program(t_data *data, t_program *prog);

//run
void	launch_threads(t_program *prog);

//time
long	get_time(t_timecode timecode);
long	get_timediff(long start, t_timecode timecode);
void	usleep_on_crack(long usec, t_program *prog);

//free
void	free_prog(t_program *prog);
void	destroy_mutexes(t_program *prog);

//get set
void	set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mtx, bool *value);
void	set_long(pthread_mutex_t *mtx, long *dest, long val);
long	get_long(pthread_mutex_t *mtx, long *val);
void	increment_long(pthread_mutex_t *mtx, long *dest);

//sync
void	wait_threads_ready(t_philo *philo);
void	desync(t_philo *philo);
void	decrement_long(pthread_mutex_t *mtx, long *dest);

//philo routine
void	write_msg(t_philo *philo, char *msg, char *color, bool prog);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

//program routine
bool	sim_finished(t_program *prog);
void	program_routine(t_program *prog);

#endif

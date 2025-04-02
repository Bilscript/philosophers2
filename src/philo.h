/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:52:07 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 16:31:47 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>


typedef struct s_table t_table;

typedef enum e_mutex
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_mutex;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef	enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_status;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}		t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}			t_philo;

struct s_table
{
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eat;
	long			start_simulation;
	long			threads_running_nbr;
	bool			end_simulation;
	bool			check_threads;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;

};

int		ft_atoi(const char *str);
void	error_exit(char *str);
void	set_input(t_table *table, char **av);
void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_mutex namecode);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_mutex namecode);
void	table_init(t_table *table);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	simulation_end(t_table *table);
void	wait_threads(t_table *table);
long	get_time(t_time_code timecode);
void	write_status(t_philo *philo, t_status status);
void	precise_usleep(long usec, t_table *table);
void	*monitoring(void *data);
void	dinner_start(t_table *table);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void	clean(t_table *table);







#endif
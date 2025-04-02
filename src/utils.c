/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:32:00 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 16:35:18 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	sign = 1;
	nb = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

void	error_exit(char *str)
{
	printf("%s\n",str);
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*res;
	
	res = malloc(bytes);
	if (!res)
		error_exit("Malloc failure.");
	return (res);
}

static void	handle_mutex_error(int status, t_mutex namecode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (status == LOCK || status == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && namecode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannoy allocate enough memory to create another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked.");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_mutex namecode)
{
	if (namecode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), namecode);
	else if (namecode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), namecode);
	else if (namecode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), namecode);
	else if (namecode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), namecode);
	else
		error_exit("Wrong namecode.");
}

static void handle_thread_error(int status, t_mutex namecode) 
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && CREATE == namecode)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (JOIN == namecode || DETACH == namecode))
		error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that specified by \
the given thread ID, thread.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread \
specifies the calling thread.");
}

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_mutex namecode)
{
	if (CREATE == namecode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), namecode);
	else if (JOIN == namecode)
		handle_thread_error(pthread_join(*thread, NULL), namecode);
	else if (DETACH == namecode)
		handle_thread_error(pthread_detach(*thread), namecode);
	else
		error_exit("Wrong opcode for thread_handle:\n use <CREATE> <JOIN> <DETACH>");
}

long get_time(t_time_code timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.");
	if (timecode == SECOND)
		return (tv.tv_sec);
	if (timecode == MILLISECOND)
		return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000);
	if (timecode == MICROSECOND)
		return (tv.tv_sec * 1000000L) + tv.tv_usec;
	error_exit("Wrong input to gettime!");
	return (0);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	past_time;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_end(table))
			break ;
		past_time = get_time(MICROSECOND) - start;
		remaining = usec - past_time;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}	
	}
}

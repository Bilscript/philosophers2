/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:42:52 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/02 17:42:52 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_mutex namecode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (status == LOCK || status == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && namecode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread \
blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannoy allocate enough memory \
to create another mutex.");
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

static void	handle_thread_error(int status, t_mutex namecode)
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

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_mutex namecode)
{
	if (CREATE == namecode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), namecode);
	else if (JOIN == namecode)
		handle_thread_error(pthread_join(*thread, NULL), namecode);
	else if (DETACH == namecode)
		handle_thread_error(pthread_detach(*thread), namecode);
	else
		error_exit("Wrong opcode for thread_handle:\n \
use <CREATE> <JOIN> <DETACH>");
}

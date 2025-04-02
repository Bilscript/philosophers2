/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:05:53 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 13:50:44 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->check_threads))
		usleep(100);
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool	res;

	safe_mutex_handle(mutex, LOCK);
	res = (*threads == philo_nbr);
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	if (!value)
		return ;
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}


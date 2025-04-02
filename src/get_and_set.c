/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:47:40 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/02 17:30:50 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	res;

	safe_mutex_handle(mutex, LOCK);
	res = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	res;

	safe_mutex_handle(mutex, LOCK);
	res = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (res);
}

bool	simulation_end(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

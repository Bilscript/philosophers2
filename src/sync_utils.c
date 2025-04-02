/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:05:53 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/03 00:26:56 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->check_threads))
		usleep(100);
}

bool	all_threads_running(pthread_mutex_t *mutex,
			long *threads, long philo_nbr)
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

void	de_sync_philo(t_philo *philo)
{
	if (philo->table->nbr_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:43:59 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/30 21:43:59 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long	past_time;
	long	tto_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return(false);
	past_time = get_time(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	tto_die = philo->table->time_to_die / 1000;
	if (past_time > tto_die)
		return (true);
	return(false);
}

void *monitoring(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->nbr_philo))
    	usleep(100);
	while (!simulation_end(table))
	{
		usleep(100);
		i = 0;
		while (i < table->nbr_philo)
		{
			if (philo_died(table->philos + i) && !simulation_end(table))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(table->philos + i, DIED);
			}
			i++;
		}
	}
	return (NULL);
}

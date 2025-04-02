/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:41:45 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/02 22:34:31 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *fork, int current)
{
	int	philo_nbr;

	philo_nbr = philo->table->nbr_philo;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[current];
		philo->second_fork = &fork[(current + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &fork[(current + 1) % philo_nbr];
		philo->second_fork = &fork[current];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nbr_philo)
	{
		philo = table->philos + i;
		philo->id = i;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_fork(philo, table->forks, i);
		i++;
	}
}

void	table_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->check_threads = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->nbr_philo);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->nbr_philo);
	while (i < table->nbr_philo)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	i = 0;
	while (i < table->nbr_philo)
	{
		set_long(&table->philos[i].philo_mutex,
			&table->philos[i].last_meal_time, table->start_simulation);
		i++;
	}
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		safe_mutex_handle(&table->philos[i].philo_mutex, DESTROY);
		safe_mutex_handle(&table->forks[i].fork, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->philos);
	free(table->forks);
}

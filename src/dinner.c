/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:31:57 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/03 00:26:18 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(philo, THINKING);
	if (philo->table->nbr_philo % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	precise_usleep(t_think * 0.42, philo->table);
}

static	void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, TAKE_FIRST_FORK);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(philo, TAKE_SECOND_FORK);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_eat > 0
		&& philo->meals_counter == philo->table->max_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_sync_philo(philo);
	while (!simulation_end(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(philo, SLEEPING);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, true);
	}
	return (NULL);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(philo, TAKE_FIRST_FORK);
	printf("salut111\n");
	while (!simulation_end(philo->table))
		usleep(50000);
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (!table->max_eat)
		return ;
	else if (table->nbr_philo == 1)
	{
		safe_thread_handle(&table->philos[0].thread_id, one_philo,
			&table->philos[0], CREATE);
	}
	else
	{
		while (++i < table->nbr_philo)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitoring, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->check_threads, true);
	i = -1;
	while (++i < table->nbr_philo)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

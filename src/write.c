/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:53:05 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 13:52:40 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status(t_philo *philo, t_status status)
{
	long	past_time;
	long	relative_time;

	past_time = get_time(MILLISECOND);
	relative_time = past_time - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) &&
		!simulation_end(philo->table))
		printf("%-6ld %d has taken a fork\n", relative_time, philo->id + 1);
	else if (status == EATING && !simulation_end(philo->table))
		printf("%-6ld %d is eating\n", relative_time, philo->id + 1);
	else if (status == SLEEPING && !simulation_end(philo->table))
		printf("%-6ld %d is sleeping\n", relative_time, philo->id + 1);
	else if (status == THINKING && !simulation_end(philo->table))
		printf("%-6ld %d is thinking\n", relative_time, philo->id + 1);
	else if (status == DIED)
		printf("%-6ld %d died\n", relative_time, philo->id + 1);

	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:23:14 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 16:37:51 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	nb;
	int		sign;

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

void	set_input(t_table *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("Les temps doivent être d'au moins 60ms");
	if (av[5])
		table->max_eat = ft_atol(av[5]);
	else
		table->max_eat = -1;
}

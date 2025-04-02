/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:32:00 by bhamani           #+#    #+#             */
/*   Updated: 2025/04/02 17:43:10 by bhamani          ###   ########.fr       */
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
	printf("%s\n", str);
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

long	get_time(t_time_code timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.");
	if (timecode == SECOND)
		return (tv.tv_sec);
	if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
	if (timecode == MICROSECOND)
		return ((tv.tv_sec * 1000000L) + tv.tv_usec);
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

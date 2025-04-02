/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamani <bhamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:41:50 by bhamani           #+#    #+#             */
/*   Updated: 2025/03/31 16:51:16 by bhamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c) {
	return (c >= '0' && c <= '9');
} 

int	check_args(char **tab, int ac)
{
	int 	i;
	int		j;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Usage:\n./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>\n");
	return (1);
	}
	while (i < ac)
	{
		j = 0;
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
			
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_table		table;

	if (!check_args(argv, argc))
	{
		printf("Erreur : Les arguments doivent être des nombres positifs.\n");
		return (1);
	}
	if (argc == 5 || argc == 6)
	{
		set_input(&table, argv);
		table_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	return (0);
}

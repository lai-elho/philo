/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:55:22 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/23 00:43:16 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(const char *str)
{
	if (str)
		printf("%s", str);
	return (1);
}

int	ft_atoi(const char *str)
{
	int				signe;
	unsigned long	nbr;

	if (!str)
		return (0);
	signe = 1;
	nbr = 0;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr >= 2147483648)
			return (0);
		str++;
	}
	if (*str)
		return (0);
	return (nbr * signe);
}

int	ft_parsing(int ac, char **av, t_table *table)
{
	table->number_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->init_fail = 0;
	table->number_limit_meals = 0;
	if (ac == 6)
		table->number_limit_meals = ft_atoi(av[5]);
	if (table->number_of_philo < 1 || table->number_of_philo > 200
		|| table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60 || table->number_limit_meals < 0)
	{
		table->init_fail = 1;
		return (1);
	}
	return (0);
}

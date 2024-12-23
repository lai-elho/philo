/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:39:01 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/23 00:39:04 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_mutex(t_table *table)
{
	if (table->init_fail == 1)
		return ;
	pthread_mutex_destroy(&table->start_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->end_mutex);
}

int	clear(t_table *table)
{
	int	i;

	if (table->forks != NULL)
	{
		i = 0;
		while (i < table->number_of_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (table->philo != NULL)
	{
		while (i < table->number_of_philo)
		{
			pthread_mutex_destroy(table->philo[i].left_fork);
			pthread_mutex_destroy(table->philo[i].right_fork);
			i++;
		}
		free(table->philo);
	}
	ft_clear_mutex(table);
	return (1);
}

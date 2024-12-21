/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:45:03 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/19 22:47:40 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

void	ft_init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		table->philo[i].table = table;
		table->philo[i].philo_id = i + 1;
		table->philo[i].nb_of_meals = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[i + 1];
		table->philo[i].last_meal_time = get_time();
		if (i == table->number_of_philo - 1)
		{
			table->philo[i].left_fork = &table->forks[0];
			table->philo[i].right_fork = &table->forks[i];
		}
	}
}

int	ft_init(t_table *table)
{
	table->forks = (pthread_mutex_t *)malloc(sizeof(*(table->forks))
			* table->number_of_philo);
	table->philo = (t_philo *)malloc(sizeof(*(table->philo))
			* table->number_of_philo);
	if (!table->philo)
	{
		table->init_fail = 1;
		return (1);
	}
	return (0);
}

void	ft_init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	table->start_simulation = get_time();
	if (table->start_simulation == -1)
		return ;
	table->end_simulation = false;
	pthread_mutex_init(&table->start_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->end_mutex, NULL);
	if (ft_init(table))
		return ;
	while (++i < table->number_of_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	ft_init_philo(table);
}
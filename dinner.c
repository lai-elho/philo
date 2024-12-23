/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:39:18 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/23 00:39:20 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_the_simulation_ended(t_table *table)
{
	pthread_mutex_lock(&table->end_mutex);
	if (table->end_simulation == true)
		return (pthread_mutex_unlock(&table->end_mutex), true);
	pthread_mutex_unlock(&table->end_mutex);
	return (false);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		ft_usleep(10);
	while (!check_the_simulation_ended(philo->table))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
		if (pthread_create(&table->philo[i].thread_id, NULL, routine,
				&table->philo[i]))
			return (exit_error("Thread creation is failed"));
	if (pthread_create(&table->monitor_id, NULL, monitor_routine, table->philo))
		return (exit_error("Thread_creation is failed"));
	i = -1;
	while (++i < table->number_of_philo)
		if (pthread_join(table->philo[i].thread_id, NULL))
			return (exit_error("Thread join is failed"));
	if (pthread_join(table->monitor_id, NULL))
		return (exit_error("Thread join is failed"));
	return (0);
}

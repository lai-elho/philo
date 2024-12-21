
#include "philo.h"

bool	check_for_meals(t_philo *philo)
{
	int	i;
	int	done_eating;

	if (philo[0].table->number_limit_meals == 0)
		return (false);
	done_eating = 0;
	i = -1;
	while (++i < philo[0].table->number_of_philo)
	{
		pthread_mutex_lock(&philo[i].table->meal_mutex);
		if (philo[i].nb_of_meals >= philo[i].table->number_limit_meals)
			done_eating++;
		pthread_mutex_unlock(&philo[i].table->meal_mutex);
	}
	if (done_eating == philo[0].table->number_of_philo)
	{
		pthread_mutex_lock(&philo[0].table->end_mutex);
		philo[0].table->end_simulation = true;
		pthread_mutex_unlock(&philo[0].table->end_mutex);
		return (true);
	}
	return (false);
}

bool	philo_is_dead(t_philo *philo, int time_to_die)
{
	int	current_time;

	pthread_mutex_lock(&philo->table->meal_mutex);
	current_time = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (current_time >= time_to_die)
		return (true);
	return (false);
}

bool	check_for_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].table->number_of_philo)
	{
		if (philo_is_dead(&philo[i], philo[i].table->time_to_die))
		{
			print_message(&philo[i], philo[i].philo_id, "died");
			pthread_mutex_lock(&philo[i].table->end_mutex);
			philo[i].table->end_simulation = true;
			pthread_mutex_unlock(&philo[i].table->end_mutex);
			return (true);
		}
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (check_for_death(philo) || check_for_meals(philo))
			break ;
	return (NULL);
}

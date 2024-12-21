
#include "philo.h"

void	print_message(t_philo *philo, int id, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->table->write_mutex);
	time = get_time() - philo->table->start_simulation;
	if (!check_the_simulation_ended(philo->table))
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	ft_sleep(t_philo *philo)
{
	print_message(philo, philo->philo_id, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	print_message(philo, philo->philo_id, "is thinking");
	if (philo->philo_id % 2 == 1)
		ft_usleep(1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, philo->philo_id, "has taken a fork");
	if (philo->table->number_of_philo == 1)
	{
		usleep(philo->table->time_to_die * 1e3);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, philo->philo_id, "has taken a fork");
	print_message(philo, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->nb_of_meals++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

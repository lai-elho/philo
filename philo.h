/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:10:45 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/23 00:45:44 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h> //mutex threrads
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					nb_of_meals;
	int					philo_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					last_meal_time;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	pthread_mutex_t		*forks;
	pthread_t			monitor_id;
	int					number_of_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	int					init_fail;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		end_mutex;
	t_philo				*philo;
}						t_table;

int						ft_parsing(int ac, char **av, t_table *table);
void					ft_init_mutexes(t_table *table);
int						dinner(t_table *table);
void					*routine(void *data);
void					*monitor_routine(void *arg);
bool					check_the_simulation_ended(t_table *table);

// utils
void					print_message(t_philo *philo, int id, char *str);
int						ft_atoi(const char *str);
int						exit_error(const char *str);
int						clear(t_table *table);
long					get_time(void);
int						ft_usleep(long time_in_ms);

// routine
void					ft_eat(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_think(t_philo *philo);
#endif
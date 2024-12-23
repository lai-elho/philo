/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:40:10 by lai-elho          #+#    #+#             */
/*   Updated: 2024/12/23 00:40:11 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
	return (0);
}

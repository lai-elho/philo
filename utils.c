
#include "philo.h"

int	ft_usleep(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
	return (0);
}


#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(ac, av, &table))
		{
			if (table.init_fail == 1)
				return (exit_error("Error: incorrect arguments\n"));
		}
		ft_init_mutexes(&table);
		if (dinner(&table))
			return (1);
		clear(&table);
	}
	else
		printf("Need argument\n");
}

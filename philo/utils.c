
#include "philo.h"

int mtx_lock(t_fork *fork)
{
    return (fork->lock);
}

// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_current_time();
// 	// printf("start: %llu\n", start);
// 	// printf("time: %u\n", time);
// 	while ((get_current_time() - start) < time)
// 		usleep(time / 10);
// 	return(0);
// }

// // Gets the current time in milliseconds
// u_int64_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		error_mes("gettimeofday");
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

int	parce_input(t_table *table, char **av)
{
	if (check_input(av) != 0)
		return (1);
	table->philo_nbr = ft_atoi(av[1]);
	if (table->philo_nbr < 1 || is_valid(table->philo_nbr))
		return (2);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	if (table->time_to_die < (unsigned long)is_valid(table->time_to_die))
		return (3);
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	if (table->time_to_eat < is_valid(table->time_to_eat))
		return (4);
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (table->time_to_sleep < is_valid(table->time_to_sleep))
		return (5);
	if (av[5])
	{
		table->max_meals = ft_atoi(av[5]);
		if (table->max_meals == 0 || is_valid(table->max_meals))
			return (6);
	}
    printf("table->time_to_die: %lu\n", table->time_to_die);
    printf("table->time_to_eat: %lu\n", table->time_to_eat);
    printf("table->time_to_sleep: %lu\n", table->time_to_sleep);
	return (0);
}

void	check_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (table->fork[i].lock == 1)
		{
			pthread_mutex_unlock(&table->fork[i].fork_mtx);
		}
	}
}



#include "philo.h"

int mtx_lock(t_fork *fork)
{
    return (fork->lock);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_current_time();
	// printf("start: %llu\n", start);
	// printf("time: %u\n", time);
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return(0);
}

// Gets the current time in milliseconds
unsigned long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_mes("gettimeofday");
	return (time.tv_sec * (unsigned long)1000 + (time.tv_usec / 1000));
}

int	parce_input(t_table *table, char **av)
{
	if (check_input(av) != 0)
		return (1);
	table->philo_nbr = ft_atoi(av[1]);
	if (table->philo_nbr < 1 || is_valid(table->philo_nbr))
		return (2);
	table->time_to_die = ft_atoi(av[2]);
	if (table->time_to_die < (unsigned long)is_valid(table->time_to_die))
		return (3);
	table->time_to_eat = ft_atoi(av[3]) * 1000; // * 1000
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
	else
		table->max_meals = -1;
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

int	check_philo_death(t_table *table)
{
	int	i;
	unsigned long	time;

	i = -1;
	time = 0;
	if (table->dead_flag == 1)
		return (1);
	if (table->thread_nbr == table->philo_nbr)
	{
		while (++i < table->philo_nbr)
		{
			// printf("\ttable->thread_nbr - %i\n", table->thread_nbr);
			// printf("\ttable->dead_flag - %i\n", table->dead_flag);
			// printf("\tphilo_id - %i\n", table->philos[i].philo_id);
			// printf("\t(get_current_time() - table->philos[i].last_eat) = %lu\n", time);
			pthread_mutex_lock(&table->mtx_eat);
			time = get_current_time() - table->philos[i].last_eat;
			pthread_mutex_unlock(&table->mtx_eat);
			if (time >= table->time_to_die && table->dead_flag != 1)
			{
				pthread_mutex_lock(&table->mtx_action);
				table->dead_flag = 1;
				
				printf("%lu %d is dead\n", get_current_time() - table->start, table->philos[i].philo_id);
				pthread_mutex_unlock(&table->mtx_action);
				// printf("\t(get_current_time() - table->philos[i].last_eat) = %lu\n", time);
				// printf("\tget_current_time() = %lu\n", get_current_time());
				// printf("\table->philos[i].last_eat) = %lu\n", table->philos[i].last_eat);
				return (time);
			}
		}
	}
	return (0);
}

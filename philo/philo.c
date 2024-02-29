/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/29 10:13:36 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
// gcc -g -pthread *.c -o philo

// Gets the current time in milliseconds
long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		perror("gettimeofday");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	parce_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		table->max_meals = ft_atoi(av[5]);
}

int	data_init(t_table *table)
{
	int	i;

	table->start = get_current_time();
	table->philos = (t_philo *)malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		error_mes("Memory allocation failed for philosophers");
	table->fork = (t_fork *)malloc(table->philo_nbr * sizeof(t_fork));
	if (table->fork == NULL)
		error_mes("Memory allocation failed for mutex");
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (table->die_flag == 1)
			return (0);
		table->fork[i].table = table;
		table->fork[i].fork_id = i + 1;
		if (pthread_mutex_init(&table->fork[i].fork_mtx, NULL) != 0)
			error_mes("Mutex init has failed\n");
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1; // Philosopher IDs start from 1
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &(table->philos[i])) != 0)
			error_mes("Thread can't be created\n");
		usleep(200);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			error_mes("Thread join failed\n"); // return (1)
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->fork[i].fork_mtx) != 0)
			error_mes("Thread join failed\n"); // return (2);
	}
	// Free allocated memory
	free(table->philos);
	free(table->fork);
	return (0);
}

/*
to check whether the time passed by the last time a philo have eaten is greater or equal to the time it takes to a philo to die from starvation, to make everything work a little bit better we are also going to check if in the momet a philo should die he's eating, in that case we'll let him survive. Other than that we are also going to check when the philo reaches the number of times he must eat and mark him as "finished", in thi way the monitor will know when all the philos have eaten.
*/
void *philo_routine(void *arg)
{
	t_philo *philo;
	t_fork	*left;
	t_fork	*right;
	int		id;
	long	nbr;

	philo = (t_philo *)arg;
	id = philo->philo_id;
	left = &philo->table->fork[id];
	right = &philo->table->fork[(id + 1) % nbr];
	while (!philo->table->die_flag)
	{
		pthread_mutex_lock(&right->fork_mtx);
        printf("%lld %d has taken a fork\n", get_current_time(), id);
        pthread_mutex_lock(&left->fork_mtx);
		printf("%lld %d has taken a fork\n", get_current_time(), id);
       

        printf("%lld %d is eating\n", get_current_time(), id);
        usleep(philo->table->time_to_eat * 1000); // Convert ms to microseconds

        pthread_mutex_unlock(&left->fork_mtx);
        pthread_mutex_unlock(&right->fork_mtx);

        printf("%lld %d is sleeping\n", get_current_time(), id);
        usleep(philo->table->time_to_sleep * 1000); // Convert ms to microseconds

        printf("%lld %d is thinking\n", get_current_time(), id);
	}
	return((void *)0);
}

int	main(int ac, char **av)
{
	t_table	table;

	(void)av;
	if (ac <= 4 || ac >= 7)
		show_options();
	table.die_flag = 0;
	parce_input(&table, av);
	data_init(&table);
	// clean_up(&table); // free all when all philo are full || 1 philo died
	return (0);
}

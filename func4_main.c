// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
// /*   Updated: 2024/02/28 21:49:04 by ohladkov         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// // ./philo 5 800 200 200 [5]
// // gcc -g -pthread *.c -o philo

// // Gets the current time in milliseconds
// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		perror("gettimeofday");
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// void	parce_input(t_table *table, char **av)
// {
// 	table->philo_nbr = ft_atoi(av[1]);
// 	table->time_to_die = ft_atoi(av[2]) * 1000;
// 	table->time_to_eat = ft_atoi(av[3]) * 1000;
// 	table->time_to_sleep = ft_atoi(av[4]) * 1000;
// 	if (av[5])
// 		table->max_meals = ft_atoi(av[5]);
// }

// void	data_init(t_table *table)
// {
// 	int	i;

// 	table->start = get_current_time();
// 	table->philos = (t_philo *)malloc(table->philo_nbr * sizeof(t_philo));
// 	if (table->philos == NULL)
// 		error_mes("Memory allocation failed for philosophers");
// 	table->fork = (t_fork *)malloc(table->philo_nbr * sizeof(t_fork));
// 	if (table->fork == NULL)
// 		error_mes("Memory allocation failed for mutex");
// 	i = -1;
// 	while (++i < table->philo_nbr)
// 	{
// 		table->fork[i].table = table;
// 		table->fork[i].fork_id = i + 1;
// 		if (pthread_mutex_init(&table->fork[i].fork_mtx, NULL) != 0)
// 			error_mes("Mutex init has failed\n");
// 		// printf("Philosopher %d is thinking\n", table->fork[i].fork_id);
// 		table->philos[i].table = table;
// 		table->philos[i].philo_id = i + 1; // Philosopher IDs start from 1
// 		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &(table->philos[i])) != 0)
// 			error_mes("Thread can't be created\n");
// 		// printf("table->philos->philo_id = %d\n", table->philos[i].philo_id);
// 		printf("time: %zu\n", get_current_time());
// 		usleep(200);
// 	}
// 	i = -1;
// 	while (++i < table->philo_nbr)
// 	{
// 		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
// 			error_mes("Thread join failed\n");
// 	}
// 	i = -1;
// 	while (++i < table->philo_nbr)
// 	{
// 		if (pthread_mutex_destroy(&table->fork[i].fork_mtx) != 0)
// 			error_mes("Thread join failed\n");
// 	}
// 	// Free allocated memory
// 	free(table->philos);
// 	free(table->fork);
// 	exit (0);
// }

// void *philo_routine(void *arg)
// {
// 	t_philo *philo;
// 	int		id;
// 	long	nbr;
	
// 	philo = (t_philo *)arg;
// 	id = philo->philo_id;
// 	// nbr = mtx->philo_nbr;
// 	// printf("Philosopher %d: Thread function\n", mtx->fork_id);
// 	printf ("Philosopher %d is thinking\n", id);
// 	//when philosopher 5 is eating he takes fork 1 and fork 5
// 	pthread_mutex_lock(&philo[(id + nbr - 1) % nbr].table->fork[(id + nbr - 1) % nbr].fork_mtx);
// 	pthread_mutex_lock(&philo[(id + 1) % nbr].table->fork[(id + 1) % nbr].fork_mtx);
// 	printf ("Philosopher %d is eating\n",id);
// 	sleep(3);
// 	pthread_mutex_unlock(&philo[(id + nbr - 1) % nbr].table->fork[(id + nbr - 1) % nbr].fork_mtx);
// 	pthread_mutex_unlock(&philo[(id + 1) % nbr].table->fork[(id + 1) % nbr].fork_mtx);
// 	printf ("Philosopher %d finished eating\n", id);

// 	return((void *)0);
// }

// int	main(int ac, char **av)
// {
// 	t_table	table;

// 	(void)av;
// 	if (ac <= 4 || ac >= 7)
// 		show_options();
// 	memset(table, 0, ft_atoi(av[1]) * sizeof(t_table));
// 	// table.die_flag = 0;
// 	parce_input(&table, av);
// 	data_init(&table);
// 	// clean_up(&table); // free all when all philo are full || 1 philo died
// 	return (0);
// }

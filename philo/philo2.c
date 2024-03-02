// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
// /*   Updated: 2024/02/27 17:52:56 by ohladkov         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// // ./philo 5 800 200 200 [5] 

// void	parce_input(t_table *table, char **av)
// {
// 	table->philo_nbr = ft_atoi(av[1]);
// 	printf("table->philo_nb = %ld\n", table->philo_nbr);
// 	table->time_to_die = ft_atoi(av[2]) * 1000;
// 	table->time_to_eat = ft_atoi(av[3]) * 1000;
// 	table->time_to_sleep = ft_atoi(av[4]) * 1000;
// 	if (av[5])
// 		table->max_meals = ft_atoi(av[5]);
// }
// void	data_init(t_table *table)
// {
// 	int	i;

// 	table->end_simulation = false;
// 	i = 0;
// 	// while (i++ < table->philo_nbr)
// 	// {
// 	// 	if (pthread_mutex_init(&table->fork->fork_mtx, NULL) != 0)
// 	// 		error_mes("Mutex init has failed\n");
// 	// 	table->fork->fork_id = i;
// 	// 	printf("table->fork->fork_id  = %d\n", table->fork->fork_id);
// 	// }
// 	i = 0;
// 	sleep(1);
// 	if (pthread_create(&table->philos->thread_id, NULL, &philo_routine, NULL) != 0)
// 		error_mes("Thread can't be created\n");
// 	table->philos->philo_id = i;
// 	printf("table->philos->philo_id = %d\n", table->philos->philo_id);
// 	// while (++i <= table->philo_nbr)
// 	// {
// 	// 	if (pthread_create(&table->philos->thread_id, NULL, philo_routine, NULL) != 0)
// 	// 		error_mes("Thread can't be created\n");
// 	// 	table->philos->philo_id = i;
// 	// 	printf("table->philos->philo_id = %d\n", table->philos->philo_id);
// 	// }
// 	i = 0;
// 	while (++i <= table->philo_nbr)
// 	{
// 		pthread_join(table->philos->thread_id, NULL);
// 	}
// }

// void *philo_routine(void *arg)
// {
// 	(void)arg;
//    printf("Thread function \n");
//    return((void *)0);
// }
// 	// pthread_mutex_lock(&table->fork->fork);
// 	// printf("1\n");
// 	// pthread_mutex_unlock(&table->fork->fork);
// 	// printf("2\n");

// int	main(int ac, char **av)
// {
// 	t_table	table;

// 	(void)av;
// 	if (ac <= 4 || ac >= 7)
// 		show_options();
// 	parce_input(&table, av);
// 	data_init(&table);
// 	// philo_routine(&table);
// 	// free_stack(&table); // when all philo are full || 1 philo died
// 	return (0);
// }
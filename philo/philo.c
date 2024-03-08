/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/08 14:56:47 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]
// gcc -g -pthread *.c -o philo

int	data_init(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		error_mes("Memory allocation failed for philosophers");
	table->fork = (t_fork *)malloc(table->philo_nbr * sizeof(t_fork));
	if (table->fork == NULL)
		error_mes("Memory allocation failed for mutex");
	table->start = get_current_time();
	table->thread_nbr = 0;
	table->dead_flag = 0;
	printf("\tstart: %ld\n", table->start);
	// printf("\tMAX_MEAL %ld\n", table->max_meals);
	pthread_mutex_init(&table->mutex, NULL);
	pthread_mutex_init(&table->mtx_action, NULL);
	pthread_mutex_init(&table->mtx_eat, NULL);
	pthread_mutex_init(&table->mtx_dead, NULL);
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->fork[i].fork_id = i;
		table->fork[i].table = table;
		table->fork[i].lock = 0;
		if (pthread_mutex_init(&table->fork[i].fork_mtx, NULL) != 0)
			error_mes("Mutex init has failed\n");
		// printf("mutex created: %d\n", i);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		// if (table->dead_flag == 1)
		// 	return (0);
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1; // Philosopher IDs start from 1
		table->philos[i].state = 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].last_eat = table->start;
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &(table->philos[i])) != 0)
			error_mes("Thread can't be created\n");
		// printf("Thread created: %d\n", i);
		table->thread_nbr += 1;
		// if (table->dead_flag == 1)
		// 	break ;
	}
	i = -1;
	while (++i < table->thread_nbr)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			error_mes("Thread join failed\n"); // return (1)
		// printf("thread joined: %d\n", i);
	}
	check_mutex(table);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->fork[i].fork_mtx) != 0)
			error_mes("Mutex destroy failed\n"); // return (2);
		// printf("mutex destroyed: %d\n", i);
	}
	if (pthread_mutex_destroy(&table->mutex) != 0)
		error_mes("Mutex destroy failed\n"); // return (2);
	if (pthread_mutex_destroy(&table->mtx_action) != 0)
		error_mes("Mutex destroy failed\n"); // return (2);
	if (pthread_mutex_destroy(&table->mtx_eat) != 0)
		error_mes("Mutex destroy failed\n"); // return (2);
	if (pthread_mutex_destroy(&table->mtx_dead) != 0)
		error_mes("Mutex destroy failed\n"); // return (2);
	// Free allocated memory
	free(table->philos);
	free(table->fork);
	return (0);
}

/*
to check whether the time passed by the last time a philo have eaten is greater 
or equal to the time it takes to a philo to die from starvation, 
to make everything work a little bit better we are also going to check if in the momet
a philo should die he's eating, in that case we'll let him survive.
Other than that we are also going to check when the philo reaches 
the number of times he must eat and mark him as "finished", 
in thi way the monitor will know when all the philos have eaten.
*/

void *philo_routine(void *arg)
{
	t_philo *philo;
	int		id;
	long	nbr;

	philo = (t_philo *)arg;
	id = philo->philo_id;
	nbr = philo->table->philo_nbr;
	philo->right_fork = &philo->table->fork[(id - 1) % nbr];
	philo->left_fork = &philo->table->fork[(id) % nbr];
	// if (philo->philo_id % 2)
	// 	usleep(15000);
	while (1)
	{
		// if (philo->table->dead_flag == 1)
		// 	break ;
		if (philo->full == 1)
			break ;
		if (check_philo_death(philo->table))
		{
			// pthread_mutex_lock(&philo->table->mtx_action);
			// philo->table->dead_flag = 1;
			// pthread_mutex_unlock(&philo->table->mtx_action);
			pthread_exit(NULL);
		}
		pthread_mutex_lock(&philo->table->mutex);
		pick_up_fork(philo);
		pthread_mutex_unlock(&philo->table->mutex);
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
		// pthread_mutex_lock(&philo->table->mtx_eat);
		// pthread_mutex_unlock(&philo->table->mtx_eat);
	}
	return((void *)0);
}

int	main(int ac, char **av)
{
	t_table	table;

	(void)av;
	if (ac <= 4 || ac >= 7)
		show_options();
	table.dead_flag = 0;
	if (parce_input(&table, av) != 0)
		show_options();
	data_init(&table);
	// clean_up(&table); // free all when all philo are full || 1 philo died
	return (0);
}



/*
./philo 5 800 200 200 7
simulation stops at 3401 2 is eating



Examples:

./philo 1 800 200 200 - Philosopher should not eat and should die.
./philo 5 800 200 200 - No Philosopher should die.
./philo 5 800 200 200 7 - No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
./philo 4 410 200 200 - No Philosopher should die.
./philo 4 310 200 100 - One Philosopher should die.
*/


/*
olenahladkovska@MacBook-Pro-Olena ph3 % ./philo 4 310 200 100
0 2 has taken a fork
0 2 has taken a fork
0 4 has taken a fork
0 4 has taken a fork
0 4 is eating
0 2 is eating
200 2 is sleeping
200 4 is sleeping
200 3 has taken a fork
200 3 has taken a fork
200 1 has taken a fork
200 1 has taken a fork
200 1 is eating
200 3 is eating
300 2 is thinking
300 4 is thinking
310 2 died
*/
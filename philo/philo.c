/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/09 23:28:43 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			error_mes("Thread join failed\n");
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->fork[i].fork_mtx) != 0)
			error_mes("Mutex destroy failed\n");
	}
	if (pthread_mutex_destroy(&table->mutex) != 0)
		error_mes("Mutex destroy failed\n");
	if (pthread_mutex_destroy(&table->mtx_print) != 0)
		error_mes("Mutex destroy failed\n");
	if (pthread_mutex_destroy(&table->mtx_action) != 0)
		error_mes("Mutex destroy failed\n");
	if (pthread_mutex_destroy(&table->mtx_dead) != 0)
		error_mes("Mutex destroy failed\n");
	free(table->philos);
	free(table->fork);
}

int	philo_mutex_init(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->mutex, NULL);
	pthread_mutex_init(&table->mtx_print, NULL);
	pthread_mutex_init(&table->mtx_action, NULL);
	pthread_mutex_init(&table->mtx_dead, NULL);
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->fork[i].fork_id = i;
		table->fork[i].table = table;
		table->fork[i].lock = 0;
		if (pthread_mutex_init(&table->fork[i].fork_mtx, NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].state = 0;
		table->philos[i].meals_counter = 0;
		table->philos[i].last_eat = table->start;
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, &(table->philos[i])) != 0)
			return (2);
	}
	return (0);
}

void	data_init(t_table *table)
{
	table->philos = (t_philo *)malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		error_mes("Memory allocation failed for philosophers");
	table->fork = (t_fork *)malloc(table->philo_nbr * sizeof(t_fork));
	if (table->fork == NULL)
		error_mes("Memory allocation failed for mutex");
	table->start = get_current_time();
	table->dead_flag = 0;
	table->all_full = 0;
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
	while (1)
	{
		if (philo->full == 1)
			break ;
		pthread_mutex_lock(&philo->table->mtx_dead);
		if (philo->table->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->table->mtx_dead);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mtx_dead);
		
		pick_up_fork(philo);
	}
	return((void *)0);
}

int	main(int ac, char **av)
{
	t_table	table;

	(void)av;
	if (ac <= 4 || ac >= 7)
		show_options();
	if (parce_input(&table, av) != 0)
		show_options();
	data_init(&table);
	if (philo_mutex_init(&table) != 0)
		free_destroy(&table);
	check_philo_death(&table);
	free_destroy(&table);
	return (0);
}

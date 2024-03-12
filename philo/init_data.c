/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:24:55 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 14:34:34 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	table->time_to_eat = ft_atoi(av[3]);
	if (table->time_to_eat < is_valid(table->time_to_eat))
		return (4);
	table->time_to_sleep = ft_atoi(av[4]);
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
	return (0);
}

int	check_input(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if ((ft_isdigit_str(av[i])) != 0)
			return (1);
	}
	return (0);
}

void	data_init(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		error_msg(table, "Memory allocation failed for philosophers");
	table->fork = (t_fork *)malloc(table->philo_nbr * sizeof(t_fork));
	if (table->fork == NULL)
		error_msg(table, "Memory allocation failed for mutex");
	table->start = get_current_time();
	table->dead_flag = 0;
	table->all_full = 0;
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->fork[i].fork_id = i;
		table->fork[i].table = table;
		table->fork[i].lock = 0;
	}
}

int	philo_mutex_init(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->mtx_print, NULL);
	pthread_mutex_init(&table->mtx_action, NULL);
	pthread_mutex_init(&table->mtx_dead, NULL);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork[i].fork_mtx, NULL) != 0)
			error_msg(table, "Failed to init mutex");
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].meals_c = 0;
		table->philos[i].last_eat = table->start;
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, \
		&(table->philos[i])) != 0)
			error_msg(table, "Failed to init mutex");
	}
	return (0);
}

void	free_destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			error_msg(table, "Thread join failed\n");
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->fork[i].fork_mtx) != 0)
			error_msg(table, "Mutex destroy failed\n");
	}
	if (pthread_mutex_destroy(&table->mtx_print) != 0)
		error_msg(table, "Mutex destroy failed\n");
	if (pthread_mutex_destroy(&table->mtx_action) != 0)
		error_msg(table, "Mutex destroy failed\n");
	if (pthread_mutex_destroy(&table->mtx_dead) != 0)
		error_msg(table, "Mutex destroy failed\n");
	free_data(table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:18 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 14:15:03 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		id;
	long	nbr;

	philo = (t_philo *)arg;
	id = philo->philo_id;
	nbr = philo->table->philo_nbr;
	philo->right_fork = &philo->table->fork[(id - 1) % nbr];
	philo->left_fork = &philo->table->fork[(id) % nbr];
	if ((id % 2) == 0)
		ft_usleep(1);
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
	return ((void *)0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac <= 4 || ac >= 7)
		show_options();
	if (parce_input(&table, av) != 0)
		show_options();
	data_init(&table);
	philo_mutex_init(&table);
	check_philo_death(&table);
	free_destroy(&table);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:25:13 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 13:32:09 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->mtx_dead);
	if (philo->table->dead_flag == 1 || philo->full == 1)
	{
		pthread_mutex_unlock(&philo->table->mtx_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mtx_dead);
	pthread_mutex_lock(&philo->table->mtx_print);
	printf("%lu %d %s\n", (get_current_time() - philo->table->start), \
	philo->philo_id, str);
	pthread_mutex_unlock(&philo->table->mtx_print);
}

int	check_philo(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mtx);
	to_print(philo, FORK);
	while (1)
	{
		pthread_mutex_lock(&philo->table->mtx_dead);
		if (philo->table->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->table->mtx_dead);
			pthread_mutex_unlock(&fork->fork_mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->mtx_dead);
		ft_usleep(philo->table->time_to_die / 2);
	}
}

int	pick_up_fork(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->table->philo_nbr == 1)
		return (check_philo(philo, philo->right_fork));
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&first_fork->fork_mtx);
	to_print(philo, FORK);
	pthread_mutex_lock(&second_fork->fork_mtx);
	to_print(philo, FORK);
	to_eat(philo);
	pthread_mutex_unlock(&first_fork->fork_mtx);
	pthread_mutex_unlock(&second_fork->fork_mtx);
	to_sleep(philo);
	return (0);
}

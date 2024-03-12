/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:24:43 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 14:34:06 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_action);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->table->mtx_action);
	to_print(philo, EAT);
	pthread_mutex_lock(&philo->table->mtx_action);
	philo->meals_c += 1;
	if (philo->meals_c != -1 && philo->meals_c == philo->table->max_meals)
	{
		philo->full = 1;
		philo->table->all_full += 1;
	}
	pthread_mutex_unlock(&philo->table->mtx_action);
	ft_usleep(philo->table->time_to_eat);
}

void	to_sleep(t_philo *philo)
{
	to_print(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
	to_print(philo, THINK);
}

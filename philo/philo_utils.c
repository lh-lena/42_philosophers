/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:25:58 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 14:34:58 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	flag_check(t_table *table, int philo_id);

int	check_philo_death(t_table *table)
{
	int				i;
	unsigned long	time;

	while (1)
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->mtx_action);
			if (table->all_full == table->philo_nbr)
			{
				pthread_mutex_unlock(&table->mtx_action);
				return (1);
			}
			time = (get_current_time() - table->philos[i].last_eat);
			if (time > table->time_to_die)
			{
				flag_check(table, table->philos[i].philo_id);
				pthread_mutex_unlock(&table->mtx_action);
				return (1);
			}
			pthread_mutex_unlock(&table->mtx_action);
		}
	}
	return (0);
}

static void	flag_check(t_table *table, int philo_id)
{
	pthread_mutex_lock(&table->mtx_dead);
	table->dead_flag = 1;
	pthread_mutex_unlock(&table->mtx_dead);
	pthread_mutex_lock(&table->mtx_dead);
	printf("%lu %d is dead\n", get_current_time() - table->start, philo_id);
	pthread_mutex_unlock(&table->mtx_dead);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(500);
	return (0);
}

// gets the current time in milliseconds
unsigned long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Failed gettimeofday\n", 20);
	return (time.tv_sec * (unsigned long)1000 + (time.tv_usec / 1000));
}

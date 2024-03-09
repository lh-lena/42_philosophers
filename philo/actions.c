
#include "philo.h"

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_action);
	philo->meals_counter += 1;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->table->mtx_action);
	
	to_print(philo, EAT, 0);
	pthread_mutex_lock(&philo->table->mtx_action);
	if (philo->meals_counter == philo->table->max_meals)
	{
		philo->full = 1;
		philo->table->all_full += 1;
	}
	pthread_mutex_unlock(&philo->table->mtx_action);
	ft_usleep(philo->table->time_to_eat);
	
}

void	to_sleep(t_philo *philo)
{
	to_print(philo, SLEEP, 0);
	usleep(philo->table->time_to_sleep);
	to_print(philo, THINK, 0);
}

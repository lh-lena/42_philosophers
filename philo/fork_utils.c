#include "philo.h"

void	to_print(t_philo *philo, char *str, int fork_id)
{
	pthread_mutex_lock(&philo->table->mtx_dead);
	if (philo->table->dead_flag == 1 || philo->full == 1)
	{
		pthread_mutex_unlock(&philo->table->mtx_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mtx_dead);
	pthread_mutex_lock(&philo->table->mtx_print);
	printf("%lu %d %s #%i\n", (get_current_time() - philo->table->start), philo->philo_id, str, fork_id);
	pthread_mutex_unlock(&philo->table->mtx_print);
}

int	pick_up_fork(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

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
	to_print(philo, FORK, first_fork->fork_id);
	pthread_mutex_lock(&second_fork->fork_mtx);
	to_print(philo, FORK, second_fork->fork_id);
	to_eat(philo);
	pthread_mutex_unlock(&philo->left_fork->fork_mtx);
	pthread_mutex_unlock(&philo->right_fork->fork_mtx);
	to_sleep(philo);
	return (0);
}

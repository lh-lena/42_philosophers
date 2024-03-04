#include "philo.h"

void	pick_up_fork(t_philo *philo)
{
	// philo->state = 1;
	// if (philo->right_fork->lock == 0 && philo->left_fork->lock == 0)
	try_to_eat(philo);
	// if (try_to_eat(philo) != 0)
		// try_to_sleep(philo);

}

// return value: 0 - is eating, 1 - no
int	try_to_eat(t_philo *philo)
{
	int	id;

	if (philo->full == 1)
		return (1);
	id = philo->philo_id;
	if (philo->right_fork->lock == 0) // && philo->left_fork->lock == 0
	{
		pthread_mutex_lock(&philo->right_fork->fork_mtx);
		philo->right_fork->lock = 1;
		printf("%llu %d has taken a right fork %i\n", (get_current_time() - philo->table->start), id, philo->right_fork->fork_id);
	}
	// else
	// 	return (1);
	if (philo->left_fork->lock == 0) // && philo->left_fork->fork_id > philo->right_fork->fork_id
	{
		pthread_mutex_lock(&philo->left_fork->fork_mtx);
		philo->left_fork->lock = 1;
		printf("%llu %d has taken a left fork %i\n", (get_current_time() - philo->table->start), id, philo->left_fork->fork_id);
	}
	else
		return (1);
	printf("%llu %d is eating\n", (get_current_time() - philo->table->start), id);
	// printf("%llu %d is eating\n", get_current_time(), id);
	philo->state = 0;
	philo->meals_counter += 1;
	usleep(philo->table->time_to_eat);
	philo->last_eat = get_current_time();
	if (philo->meals_counter == philo->table->max_meals)
	{
		philo->full = 1;
		printf("\tphilo->full %d\n", id);
	}
	if (philo->right_fork->lock == 1)
	{
		philo->right_fork->lock = 0;
		pthread_mutex_unlock(&philo->right_fork->fork_mtx);
	}
	if (philo->left_fork->lock == 1)
	{
		philo->left_fork->lock = 0;
		pthread_mutex_unlock(&philo->left_fork->fork_mtx);
	}
	to_sleep(philo);
	return (0);
}

void	to_sleep(t_philo *philo)
{
	if (philo->full == 1 || philo->table->dead_flag == 1 || philo->meals_counter == 0)
		return ;
	philo->state = 2;
	printf("%llu %d is sleeping\n", (get_current_time() - philo->table->start), philo->philo_id);
	usleep(philo->table->time_to_sleep);
	if ((get_current_time() - philo->last_eat) >= philo->table->time_to_die)
		philo->table->dead_flag = 1;
	philo->state = 1;
}

void	to_think(t_philo *philo)
{
	if (philo->full == 1 || philo->table->dead_flag == 1 || philo->meals_counter == 0)
		return ;
	if (philo->state != 0 && philo->state != 2)
	{
		printf("%llu %d is thinking\n", (get_current_time() - philo->table->start), philo->philo_id);
		usleep(philo->table->time_to_sleep);
		if ((get_current_time() - philo->last_eat) >= philo->table->time_to_die)
			philo->table->dead_flag = 1;
		philo->state = 2;
	}
}
/* 
int	try_to_eat(t_philo *philo)
{
	int	id;
	int	nbr;

	id = philo->philo_id;
	nbr = philo->table->philo_nbr;
	if (philo->state == 1 && philo->table->philos[id % nbr].state != 0 \
	&& philo->table->philos[(id - 1) % nbr].state != 0)
	{
		if (philo->right_fork->lock == 0 && philo->left_fork->lock == 0)
		{
			pthread_mutex_lock(&philo->right_fork->fork_mtx);
			philo->right_fork->lock = 1;
			printf("%lu %d has taken a right fork %i\n", get_current_time(), id, philo->right_fork->fork_id);
		}
		if (philo->left_fork->lock == 0 && philo->left_fork->fork_id > philo->right_fork->fork_id)
		{
			pthread_mutex_lock(&philo->left_fork->fork_mtx);
			philo->left_fork->lock = 1;
			printf("%lu %d has taken a left fork %i\n", get_current_time(), id, philo->left_fork->fork_id);
		}
		else
			return (1);
		printf("%lu %d is eating\n", get_current_time(), philo->philo_id);
		philo->state = 0;
		philo->meals_counter += 1;
		usleep(philo->table->time_to_eat);
		// philo->last_eat = get_current_time();
		if (philo->meals_counter == philo->table->max_meals)
			philo->full = 1;
		if ((get_current_time() - philo->last_eat) >= philo->table->time_to_die)
			philo->table->dead_flag = 1;
		return (0);
	}
	return (1);
}
 */
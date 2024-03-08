#include "philo.h"

// int	pick_up_fork(t_philo *philo)
// {
// 	int	id;
// 	int	nbr;

// 	id = philo->philo_id;
// 	nbr = philo->table->philo_nbr;
// 	if (philo->full != 1 && philo->table->dead_flag != 1)
// 	{
// 		// if (philo->table->philos[(id - 1) % nbr].state == 0 || philo->table->philos[id % nbr].state == 0)
// 		// 	return (1);
// 		if (philo->left_fork->lock == 0 && philo->table->philos[(id + 1) % nbr].state != 0) // && philo->table->philos[id % nbr].state != 0) // && philo->left_fork->lock == 0 // && philo->table->philos[(id - 1) % nbr].state != 0 //  && philo->table->philos[(id - 1) % nbr].state != 0
// 		{
// 			printf("\tid = %d | left | philos[id o/o nbr].id = %d\n", philo->philo_id, philo->table->philos[(id) % nbr].philo_id);
// 			// printf("\tid = %d | right | philos[(id) o/o nbr].state = %d\n", philo->philo_id, philo->table->philos[(id - 2 + nbr) % nbr].state);
// 			pthread_mutex_lock(&philo->left_fork->fork_mtx);
// 			philo->left_fork->lock = 1;
// 			if (philo->right_fork->lock == 0 && philo->table->philos[(id - 1) % nbr].state != 0) // && philo->left_fork->fork_id > philo->right_fork->fork_id //  && philo->table->philos[(id + 1) % nbr].state != 0 // && philo->table->philos[id % nbr].state != 0
// 			{
// 				// printf("\tid = %d | right | philos[(id) o/o nbr].id = %d\n", philo->philo_id, philo->table->philos[(id - 2 + nbr) % nbr].philo_id);
// 				// printf("\tid = %d | left | philos[id o/o nbr].state = %d\n", philo->philo_id, philo->table->philos[(id) % nbr].state);
// 				pthread_mutex_lock(&philo->right_fork->fork_mtx);
// 				philo->right_fork->lock = 1;
// 				printf("%lu %d has taken a right fork %i\n", (get_current_time() - philo->table->start), id, philo->right_fork->fork_id);
// 			}
// 			else
// 			{
// 				pthread_mutex_unlock(&philo->left_fork->fork_mtx);
// 				philo->left_fork->lock = 0;
// 				return (1);
// 			}
// 			printf("%lu %d has taken a left fork %i\n", (get_current_time() - philo->table->start), id, philo->left_fork->fork_id);
// 			pthread_mutex_lock(&philo->table->mtx_eat);
// 			philo->state = 0;
// 			// printf("%lu %d is eating\n", (get_current_time() - philo->table->start), philo->philo_id);
// 			pthread_mutex_unlock(&philo->table->mtx_eat);
// 			if (philo->right_fork->lock == 1)
// 			{
// 				philo->right_fork->lock = 0;
// 				pthread_mutex_unlock(&philo->right_fork->fork_mtx);
// 			}
// 			if (philo->left_fork->lock == 1)
// 			{
// 				philo->left_fork->lock = 0;
// 				pthread_mutex_unlock(&philo->left_fork->fork_mtx);
// 			}
// 		}
// 	}
// 	return (0);
// }



int	pick_up_fork(t_philo *philo)
{
	int	id;
	// int	nbr;
	pthread_mutex_lock(&philo->table->mtx_dead);
	if (philo->full == 1 || philo->table->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mtx_dead);
	id = philo->philo_id;
	// nbr = philo->table->philo_nbr;

		// if (philo->table->philos[(id - 1) % nbr].state == 0 || philo->table->philos[id % nbr].state == 0)
		// 	return (1);
		pthread_mutex_lock(&philo->table->mtx_eat);
		if (philo->right_fork->lock == 0) // && philo->table->philos[id % nbr].state != 0) // && philo->left_fork->lock == 0 // && philo->table->philos[(id - 1) % nbr].state != 0 //  && philo->table->philos[(id - 1) % nbr].state != 0
		{
			// printf("\tid = %d | left | philos[id o/o nbr].id = %d\n", philo->philo_id, philo->table->philos[(id) % nbr].philo_id);
			// printf("\tid = %d | right | philos[(id) o/o nbr].state = %d\n", philo->philo_id, philo->table->philos[(id - 2 + nbr) % nbr].state);
			pthread_mutex_lock(&philo->right_fork->fork_mtx);
			philo->right_fork->lock = 1;
			if (philo->left_fork->lock == 0) // && philo->left_fork->fork_id > philo->right_fork->fork_id //  && philo->table->philos[(id + 1) % nbr].state != 0 // && philo->table->philos[id % nbr].state != 0
			{
				// printf("\tid = %d | right | philos[(id) o/o nbr].id = %d\n", philo->philo_id, philo->table->philos[(id - 2 + nbr) % nbr].philo_id);
				// printf("\tid = %d | left | philos[id o/o nbr].state = %d\n", philo->philo_id, philo->table->philos[(id) % nbr].state);
				pthread_mutex_lock(&philo->left_fork->fork_mtx);
				printf("%lu %d has taken a left fork %i\n", (get_current_time() - philo->table->start), id, philo->left_fork->fork_id);
				philo->left_fork->lock = 1;
			}
			else
			{
				pthread_mutex_unlock(&philo->right_fork->fork_mtx);
				philo->right_fork->lock = 0;
				return (1);
			}
			printf("%lu %d has taken a right fork %i\n", (get_current_time() - philo->table->start), id, philo->right_fork->fork_id);
			philo->state = 0;
			// printf("%lu %d is eating\n", (get_current_time() - philo->table->start), philo->philo_id);
			pthread_mutex_unlock(&philo->table->mtx_eat);
			
		}
	return (0);
}

void	to_sleep(t_philo *philo)
{
	if ( philo->state == 0 && philo->table->dead_flag != 1) // philo->full != 1 &&  && philo->table->dead_flag != 1
	{
		printf("%lu %d is sleeping\n", (get_current_time() - philo->table->start), philo->philo_id);
		usleep(philo->table->time_to_sleep);
		pthread_mutex_lock(&philo->table->mtx_eat);
		philo->state = 1;
		pthread_mutex_unlock(&philo->table->mtx_eat);
	}
}

void	to_think(t_philo *philo)
{
	if (philo->full != 1 && philo->meals_counter > 0 && philo->table->dead_flag != 1 && philo->state != 3)
	{
		printf("%lu %d is thinking\n", (get_current_time() - philo->table->start), philo->philo_id);
		while (philo->left_fork->lock != 0 || philo->right_fork->lock != 0)
			usleep(50);
		pthread_mutex_lock(&philo->table->mtx_eat);
		philo->state = 3;
		pthread_mutex_unlock(&philo->table->mtx_eat);
	}
}

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_eat);
	if (philo->state != 0 || philo->full == 1 || philo->table->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->mtx_eat);
		return ;
	}
	pthread_mutex_unlock(&philo->table->mtx_eat);
		philo->last_eat = get_current_time();
		philo->meals_counter += 1;
		printf("%lu %d is eating\n", (get_current_time() - philo->table->start), philo->philo_id);
		usleep(philo->table->time_to_eat);
		if (philo->meals_counter == philo->table->max_meals)
		{
			philo->full = 1;
			printf("\tphilo->full %d\n",  philo->philo_id);
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
}

/* 
int pick_up_fork(t_philo *philo) {
    int id = philo->philo_id;
    // int nbr = philo->table->philo_nbr;

    if (philo->full == 1 || philo->table->dead_flag == 1)
        return 1;

    pthread_mutex_lock(&philo->right_fork->fork_mtx);
    if (philo->right_fork->lock == 0) {
        philo->right_fork->lock = 1;
        printf("%lu %d has taken a right fork %i\n", (get_current_time() - philo->table->start), id, philo->right_fork->fork_id);
    } else {
        pthread_mutex_unlock(&philo->right_fork->fork_mtx);
		philo->right_fork->lock = 0;
        return 1; // Right fork not available, return without acquiring the left fork
    }

    pthread_mutex_lock(&philo->left_fork->fork_mtx);
    if (philo->left_fork->lock == 0) {
        philo->left_fork->lock = 1;
        printf("%lu %d has taken a left fork %i\n", (get_current_time() - philo->table->start), id, philo->left_fork->fork_id);
    } else {
        // Release the right fork if the left fork cannot be acquired
        pthread_mutex_unlock(&philo->right_fork->fork_mtx);
        philo->right_fork->lock = 0;
        return 1; // Left fork not available
    }
    philo->state = 0; // Both forks acquired, philosopher is now eating
    return 0;
}
 */
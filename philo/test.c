// #include "philo.h"

// // Function for philosopher thread routine
// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;

//     while (!philo->table->dead_flag)
//     {
//         // Lock the mutex for the table to prevent other philosophers from accessing it simultaneously
//         pthread_mutex_lock(&philo->table->mutex);

//         // Try to pick up left fork
//         if (pthread_mutex_trylock(&philo->left_fork->fork_mtx) == 0)
//         {
//             philo->left_fork->lock = 1; // Set the lock flag to indicate that the fork is taken
//             printf("%lu Philosopher %d picked up left fork %d\n", (get_current_time() - philo->table->start), philo->philo_id, philo->left_fork->fork_id);

//             // Try to pick up right fork
//             if (pthread_mutex_trylock(&philo->right_fork->fork_mtx) == 0)
//             {
//                 philo->right_fork->lock = 1; // Set the lock flag to indicate that the fork is taken
//                 printf("%lu Philosopher %d picked up right fork %d\n", (get_current_time() - philo->table->start), philo->philo_id, philo->right_fork->fork_id);

//                 // Philosopher can eat
//                 philo->state = 0; // Set state to eating
//                 philo->last_eat = get_current_time(); // Update last_eat time
//                 printf("%lu Philosopher %d is eating\n", (get_current_time() - philo->table->start), philo->philo_id);
//                 usleep(philo->table->time_to_eat); // Simulate eating time

//                 // Release right fork
//                 pthread_mutex_unlock(&philo->right_fork->fork_mtx);
//                 philo->right_fork->lock = 0; // Reset the lock flag

//                 // Release left fork
//                 pthread_mutex_unlock(&philo->left_fork->fork_mtx);
//                 philo->left_fork->lock = 0; // Reset the lock flag

//                 // Philosopher is done eating
//                 philo->meals_counter++; // Increment meals counter
//                 if (philo->meals_counter >= philo->table->max_meals)
//                 {
//                     philo->full = 1; // Set full flag if max meals reached
//                     printf("%lu Philosopher %d is full\n", (get_current_time() - philo->table->start), philo->philo_id);
//                 }
//             }
//             else
//             {
//                 // Release left fork if right fork is not available
//                 pthread_mutex_unlock(&philo->left_fork->fork_mtx);
//                 philo->left_fork->lock = 0; // Reset the lock flag
//             }
//         }

//         // Release the mutex for the table
//         pthread_mutex_unlock(&philo->table->mutex);

//         // Philosopher sleeps
//         philo->state = 2; // Set state to sleeping
//         printf("%lu Philosopher %d is sleeping\n", (get_current_time() - philo->table->start), philo->philo_id);
//         usleep(philo->table->time_to_sleep); // Simulate sleeping time

//         // Philosopher thinks (not specified in problem)
//         philo->state = 3; // Set state to thinking
//         printf("%lu Philosopher %d is thinking\n", (get_current_time() - philo->table->start), philo->philo_id);
//     }

//     return NULL;
// }


// -------------
// Function for philosopher thread routine
// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;

//     while (!philo->table->dead_flag)
//     {
//         // Check if philosopher is alive
//         if ((get_current_time() - philo->last_eat) >= philo->table->time_to_die)
//         {
//             printf("%lu Philosopher %d died\n", (get_current_time() - philo->table->start), philo->philo_id);
//             philo->table->dead_flag = 1; // Set dead flag
//             break; // Exit loop if philosopher is dead
//         }

//         // Lock the mutex for the table to prevent other philosophers from accessing it simultaneously
//         pthread_mutex_lock(&philo->table->mutex);

//         // Try to pick up left fork
//         if (pthread_mutex_trylock(&philo->left_fork->fork_mtx) == 0)
//         {
//             philo->left_fork->lock = 1; // Set the lock flag to indicate that the fork is taken
//             printf("%lu Philosopher %d picked up left fork %d\n", (get_current_time() - philo->table->start), philo->philo_id, philo->left_fork->fork_id);

//             // Try to pick up right fork
//             if (pthread_mutex_trylock(&philo->right_fork->fork_mtx) == 0)
//             {
//                 philo->right_fork->lock = 1; // Set the lock flag to indicate that the fork is taken
//                 printf("%lu Philosopher %d picked up right fork %d\n", (get_current_time() - philo->table->start), philo->philo_id, philo->right_fork->fork_id);

//                 // Philosopher can eat
//                 philo->state = 0; // Set state to eating
//                 philo->last_eat = get_current_time(); // Update last_eat time
//                 printf("%lu Philosopher %d is eating\n", (get_current_time() - philo->table->start), philo->philo_id);
//                 usleep(philo->table->time_to_eat); // Simulate eating time

//                 // Release right fork
//                 pthread_mutex_unlock(&philo->right_fork->fork_mtx);
//                 philo->right_fork->lock = 0; // Reset the lock flag

//                 // Release left fork
//                 pthread_mutex_unlock(&philo->left_fork->fork_mtx);
//                 philo->left_fork->lock = 0; // Reset the lock flag

//                 // Philosopher is done eating
//                 philo->meals_counter++; // Increment meals counter
//                 if (philo->meals_counter >= philo->table->max_meals)
//                 {
//                     philo->full = 1; // Set full flag if max meals reached
//                     printf("%lu Philosopher %d is full\n", (get_current_time() - philo->table->start), philo->philo_id);
//                 }
//             }
//             else
//             {
//                 // Release left fork if right fork is not available
//                 pthread_mutex_unlock(&philo->left_fork->fork_mtx);
//                 philo->left_fork->lock = 0; // Reset the lock flag
//             }
//         }

//         // Release the mutex for the table
//         pthread_mutex_unlock(&philo->table->mutex);

//         // Philosopher sleeps
//         philo->state = 2; // Set state to sleeping
//         printf("%lu Philosopher %d is sleeping\n", (get_current_time() - philo->table->start), philo->philo_id);
//         usleep(philo->table->time_to_sleep); // Simulate sleeping time

//         // Philosopher thinks (not specified in problem)
//         philo->state = 3; // Set state to thinking
//         printf("%lu Philosopher %d is thinking\n", (get_current_time() - philo->table->start), philo->philo_id);
//     }

//     return NULL;
// }

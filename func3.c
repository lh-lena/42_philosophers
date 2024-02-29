// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// typedef struct {
//     int num_philosophers;
//     pthread_mutex_t *forks;
//     pthread_t *philosopher_threads;
// } DiningPhilosophers;

// void *philosopher(void *arg) {
//     int philosopher_id = *((int *)arg);
//     DiningPhilosophers *dp = (DiningPhilosophers *)(((int *)arg) + 1);
//     int left_fork = philosopher_id;
//     int right_fork = (philosopher_id + 1) % dp->num_philosophers;

//     while (1) {
//         printf("Philosopher %d is thinking\n", philosopher_id);
//         sleep(1);

//         printf("Philosopher %d is hungry\n", philosopher_id);
//         pthread_mutex_lock(&dp->forks[left_fork]);
//         pthread_mutex_lock(&dp->forks[right_fork]);

//         printf("Philosopher %d is eating\n", philosopher_id);
//         sleep(1);

//         pthread_mutex_unlock(&dp->forks[left_fork]);
//         pthread_mutex_unlock(&dp->forks[right_fork]);
//     }

//     return NULL;
// }

// void init_dining_philosophers(DiningPhilosophers *dp, int num_philosophers) {
//     dp->num_philosophers = num_philosophers;

//     // Initialize mutexes for forks
//     dp->forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_mutex_init(&dp->forks[i], NULL);
//     }

//     // Create threads for philosophers
//     dp->philosopher_threads = malloc(num_philosophers * sizeof(pthread_t));
//     int *philosopher_ids = malloc(num_philosophers * sizeof(int));
//     for (int i = 0; i < num_philosophers; i++) {
//         philosopher_ids[i] = i;
//         pthread_create(&dp->philosopher_threads[i], NULL, philosopher, &philosopher_ids[i]);
//     }
// }

// void destroy_dining_philosophers(DiningPhilosophers *dp) {
//     // Join threads
//     for (int i = 0; i < dp->num_philosophers; i++) {
//         pthread_join(dp->philosopher_threads[i], NULL);
//     }

//     // Clean up
//     free(dp->philosopher_threads);
//     for (int i = 0; i < dp->num_philosophers; i++) {
//         pthread_mutex_destroy(&dp->forks[i]);
//     }
//     free(dp->forks);
// }

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         printf("Usage: %s <number_of_philosophers>\n", argv[0]);
//         return 1;
//     }

//     int num_philosophers = atoi(argv[1]);
//     if (num_philosophers <= 0) {
//         printf("Invalid number of philosophers\n");
//         return 1;
//     }

//     DiningPhilosophers dp;
//     init_dining_philosophers(&dp, num_philosophers);
//     destroy_dining_philosophers(&dp);

//     return 0;
// }

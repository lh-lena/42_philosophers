/*
    https://medium.com/@ayogun/posix-thread-pthread-library-8915d867201f
*/

/* #include <pthread.h>  

int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);                                                 
Returns: 0 if OK, error number on failure

pthread_join() blocks the thread at the call point until the related thread terminates. Of course, if the pthread_join function does not encounter an error, it blocks. For example, if the thread specified in the first argument of pthread_join() has already terminated, then EINVAL returns with an error value and the block does not occur.


*/

/*pthread_t tid;

void * threadFunc(void *arg)
{
   printf("Thread function \n");
   return((void *)0);
}
int main(void)
{

   int err;
   err = pthread_create(&tid, NULL, threadFunc, NULL);
   if (0 != err)
      printf("can’t create thread \n");
   printf("main thread \n");
   sleep(1);
   
   return 0;
}*/

/*
#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}
// #6 https://www.youtube.com/watch?v=ln3el6PR__Q&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=6
void    *roll_dice()
{
    int value = (rand() % 6) + 1;
    printf("%d\n", value);
}

int main(void)
{
	pthread_t	th[10];
    int i = 0;
    int* res;
    srand(time(NULL));

	pthread_mutex_init(&mutex, NULL);
    while (i < 4)
    {
     	if (pthread_create(th + i, NULL, &roll_dice, NULL) != 0)
	    {
            perror("Failed to create thread\n");
            return (1);
        }
        printf("Thread %d has started\n", i);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (pthread_join(th[i], (void **)&res) != 0)
            return (2);
        printf("Thread %d has finished execution\n", i);
        i++;
    }
	pthread_mutex_destroy(&mutex);
	printf("mails = %d\n", mails);
	return (0);
}
*/

/*
to print thred's pid

pthread_t th = pthread_self();
printf("%ul\n", th);

*/

/*

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *thread(void *arg)
{
    char *ret;
    printf("thread() entered with argument '%s'\n", arg);
    if ((ret == (char*)malloc(20)) == NULL)
    {
        perror("malloc() error");
        exit(2);
    }
    strcpy(ret, "This is a test");
    pthread_exit(ret);
}

void main(void)
{
    pthrea_t thid;
    void*   ret;

    if (pthread_create(&thid, NULL, thread, "thread 1") != 0)
    {
        perror("pthread_create() error");
        exit(1);
    }
    if (pthread_join(thid, &ret) != 0)
    {
        perror("thread_create() perror");
        exit(3);
    }
    printf("thread exited with - %s\n", ret);
}
*/

/*
#include <pthread.h>
#include <stdio.h>

int main(void)
{
    pthread_mutex_t fork_mutex;
    
    pthread_mutex_init(&fork_mutex, NULL);
    
    pthread_mutex_lock(&fork_mutex);
    set_unavailable(fork);
    pthread_mutex_unlock(&fork_mutex);
    
    pthread_mutex_destroy(&fork_mutex);
    
    return (0);
}
*/

/*
struct    timeval  {
    time_t        tv_sec ;   //used for seconds
    suseconds_t       tv_usec ;   //used for microseconds
}
1 second = 1 000 milisec.

// return time in  milliseconds
uint64_t    get_time(void)
{
    struct  timeval    tv;

    if (gettimeofday(&tv, NULL))
        return (0);
    return ((tv.tv_sec * (unt64_t)1000) + (tv.tv_usec / 1000));
}
// ------------------------------ 
void       my_time(void)
{
    struct  timeval start_time;
    struct  timeval end_time;
    long            requested_sleep_time;
    long            actual_sleep_time;

    requested_sleep_time = 200 * 1000; // 200 milisec 200 000
    gettimeofday(&start_time, NULL);
    usleep(requested_sleep_time);
    gettimeofday(&end_time, NULL);
    actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

    printf("requested_sleep_time %ld\n", requested_sleep_time);
    printf("actual_sleep_time %ld\n", actual_sleep_time);
}

int main(void)
{
    my_time();
    return (0);
}
// requested_sleep_time 200000
// actual_sleep_time 200233
*/

/*
// https://www.youtube.com/watch?v=UGQsvVKwe90 
typedef struct data_s
{
    int num;
    pthread_mutex_t mutex;
} data_t;

data_t  *init_data()
{
    data_t  *data;

    data = malloc(sizeof(data_t));
    pthread_mutex_init(&data->mutex, NULL);
    return (data);
}

void    free_data(data_t *data)
{
    pthread_mutex_destroy(&data->mutex);
    free(data);
}

void    exit_on_error(data_t *data, int num)
{
    free(data);
    exit(num);
}

void    *routine(void *arg)
{
    data_t      *data;
    int i;

    data = (data_t *)arg;
    i = 0;
    while (i < 10000)
    {
        pthread_mutex_lock(&data->mutex); //locked
        (data->num)++;
        pthread_mutex_unlock(&data->mutex);
        i++;
    }
    return (NULL);
}
void    example()
{
    data_t  *data;
    pthread_t  t1;
    pthread_t  t2;

    data = init_data();
    if (pthread_create(&t1, NULL, routine, data) != 0)
        exit_on_error(data, 2);
    if (pthread_create(&t2, NULL, routine, data) != 0)
        exit_on_error(data, 3);

    if (pthread_join(t1, NULL) != 0)
        exit_on_error(data, 4);
    if (pthread_join(t2, NULL) != 0)
        exit_on_error(data, 5);
    printf("Num = %d\n", data->num);
    free_data(data);
}

int main(void)
{
    example();
    return (0);
    // Num = 16363
}
*/

/* 
It's the problem of operation system which deals with resource allocation.
All philosophers represent the prosseses and forks / chopstick - resources that has to be shared beetwen the prosseses.
Limited resources and habe to be shared between all prosseses in a synchronized manner without violating any rules. So there may be resourcs that can be used only one process at a time so if other processor try to access the same resoure at the same time.

Every prosse is a specific number of threads. 


!! a way to avoid "race conditions" => lock the ledger until completion

*/

// / gcc -g -pthread philo.c -o philo
/*
Philosophers with threads and mutexes
Arguments: 
1 number_of_philosophers 
2 time_to_die time_to_eat
3 time_to_sleep
4 [number_of_times_each_philosopher_must_eat]

- thinking 
- sleeping 
- eating (if both folks ae available) | pick up or put down 
--------
think unless the left fork is available; when it is, pick it up;
think unless the right fork is available; when it is, pick it up;
when both forks are held, eat for a fixed amount of time;
put the left fork down;
put the right fork down;
repeat from the beginning.
However, each philosopher will think for an undetermined amount of time and may end up holding a left fork thinking, staring at the right side of the plate, unable to eat because there is no right fork, until he starves.
------

To solve this problem, we can use this strategy:

Consider five philosophers: P0,P1,P2,P3,P4 &

five chopsticks: C0,C1,C2,C3,C4

Initially we let P0 enter into the dining room.

Since nobody else is present there all the chopsticks are free and P0 acquires chopsticks C0 and C1 and starts eating.

-------------------------  

even:
time_to_die = time_to_eat + tme_to sleep + 10

odd:
time_to_die = time_to_eat * 2 + tme_to sleep + 10

1) odd sleep(time_to_eat / 2)
2)  odd start taking from right fork, 
	even start taking from left fork
3) all philosophers take fro right fork, except for the last one.
-------------------------------
External functs.:
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. 
Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right side. 
If there is only one philosopher, there should be only one fork on the table. | 1 philo = 1 folk 
• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them. 
*/

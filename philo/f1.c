#include "philo.h"

// int	ft_usleep(unsigned long time)
// {
// 	unsigned long	start;

// 	start = get_current_time();
// 	// printf("start: %llu\n", start);
// 	// printf("time: %u\n", time);
// 	while ((get_current_time() - start) < time)
// 		usleep(time / 10);
// 	return(0);
// }

// // Gets the current time in milliseconds
// unsigned long	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		error_mes("gettimeofday");
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }



// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_current_time();
// 	// printf("start: %llu\n", start);
// 	// printf("time: %u\n", time);
// 	while ((get_current_time() - start) < time)
// 		usleep(time / 10);
// 	return(0);
// }

// // Gets the current time in milliseconds
// u_int64_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		error_mes("gettimeofday");
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }
// https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

// Improved version of sleep function
// int	ft_usleep(size_t milliseconds)
// {
// 	size_t	start;

// 	start = get_current_time();
// 	while ((get_current_time() - start) < milliseconds)
// 		usleep(500);
// 	return (0);
// }

// Gets the current time in milliseconds
// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// https://github.com/TommyJD93/Philosophers?tab=readme-ov-file#step1

// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;
// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return(0);
// }

// A fucntion to take the current time in milliseconds.
// u_int64_t	get_time(void)
// {
// 	struct timeval	tv;
	
// 	if (gettimeofday(&tv, NULL))
// 		return (error("gettimeofday() FAILURE\n", NULL));
// 	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
// }






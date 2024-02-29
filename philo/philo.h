/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/29 10:12:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// ANSI color codes    
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	int				fork_id;
	t_table			*table;
}				t_fork;

typedef struct s_philo
{
	int			philo_id;
	// long		meals_counter;
	// bool		full;
	long		last_eat;
	t_fork		*left_fork;
	t_fork		*right_fork;
	// pthread_mutex_t	*fork_r;
	// pthread_mutex_t	fork_l;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start;
	bool	die_flag; // philo die or philo full
	t_fork	*fork;
	t_philo	*philos;
};

void	error_mes(char *s);
void	show_options(void);
long	ft_atoi(const char *str);
// char	**ft_split(char const *s, char c);

void	*philo_routine(void *arg);
int		data_init(t_table *table);
void	parce_input(t_table *table, char **av);

#endif

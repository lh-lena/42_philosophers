/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:55:28 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 12:41:23 by ohladkov         ###   ########.fr       */
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
# include <string.h>

// ANSI color codes    
# define R "\033[1;31m"
# define RESET "\033[0m"

# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "dead"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	int				fork_id;
	int				lock;
	t_table			*table;
}				t_fork;

typedef struct s_philo
{
	int					philo_id;
	long				meals_c;
	int					full;
	unsigned long		last_eat;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}				t_philo;

struct s_table
{
	long			philo_nbr;
	unsigned long	time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	long			start;
	int				dead_flag;
	int				all_full;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_action;
	pthread_mutex_t	mtx_dead;
	t_fork			*fork;
	t_philo			*philos;
};

void			error_msg(t_table *table, char *s);
int				parce_input(t_table *table, char **av);
int				check_input(char **av);
int				is_valid(int i);
int				ft_isdigit_str(char *s);
void			show_options(void);
long			ft_atoi(const char *str);
void			data_init(t_table *table);
int				philo_mutex_init(t_table *table);
void			free_data(t_table *table);
void			free_destroy(t_table *table);
void			*philo_routine(void *arg);
unsigned long	get_current_time(void);
int				pick_up_fork(t_philo *philo);
void			to_eat(t_philo *philo);
void			to_sleep(t_philo *philo);
int				ft_usleep(unsigned long time);
int				check_philo_death(t_table *table);
void			to_print(t_philo *philo, char *str);

#endif
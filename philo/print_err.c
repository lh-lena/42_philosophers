/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:15:06 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/03 23:10:53 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_options(void)
{
	printf("[Error]: Invalid arguments\n");
	printf("Expected arguments:\n");
	printf("\t [1]: number_of_philosophers\n");
	printf("\t [2]: time_to_die\n");
	printf("\t [3]: time_to_eat\n");
	printf("\t [4]: time_to_sleep\n");
	printf("optional [5]: ");
	printf("number_of_times_each_philosopher_must_eat\n");
	printf("./philo 5 800 200 200 [5]\n");
	exit(EXIT_FAILURE);
}

void	error_mes(char *s)
{
	printf(R"[Error]: %s\n"RESET, s);
	exit(EXIT_FAILURE);
}

/* void	show_options(void)
{
	printf(R"[Error]: Invalid arguments\n"RESET);
	printf("Expected arguments:\n");
	printf("\t [1]: number_of_philosophers\n");
	printf("\t [2]: time_to_die\n");
	printf("\t [3]: time_to_eat\n");
	printf("\t [4]: time_to_sleep\n");
	printf("optional [5]: ");
	printf("number_of_times_each_philosopher_must_eat\n");
	printf(G"./philo 5 800 200 200 [5]\n"RESET);
	exit(EXIT_FAILURE);
} */

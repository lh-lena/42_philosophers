/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:15:06 by ohladkov          #+#    #+#             */
/*   Updated: 2024/03/10 14:35:08 by ohladkov         ###   ########.fr       */
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

void	error_msg(t_table *table, char *s)
{
	printf(R"[Error]: %s\n"RESET, s);
	free_data(table);
	exit(EXIT_FAILURE);
}

void	free_data(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->fork)
		free(table->fork);
}

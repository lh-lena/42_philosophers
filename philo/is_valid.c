/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:14:21 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/29 13:19:14 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

int	ft_issign(int c)
{
	return (c == 43 || c == 45);
}

int	ft_isdigit_str(char *s)
{
	int	j;

	j = 0;
	if (ft_issign(s[j]))
	{
		j++;
		while (s[j])
		{
			if (!ft_isdigit(s[j]))
				return (1);
			j++;
		}
	}
	else
	{
		while (s[j])
		{
			if (ft_isdigit(s[j]) == 0)
				return (1);
			j++;
		}
	}
	return (0);
}

int	is_valid(int i)
{
	return ((i < 0 || i > INT_MAX));
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	total;

	sign = 1;
	total = 0;
	while (*str != '\0' && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		total *= 10;
		total += (*str - '0');
		str++;
	}
	// is_valid(total * sign);
	return (total * sign);
}

int		check_input(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if ((ft_isdigit_str(av[i])) != 0)
			return (1);
	}
	return (0);
}
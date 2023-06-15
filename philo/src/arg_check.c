/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:50:01 by andrefranci       #+#    #+#             */
/*   Updated: 2023/06/15 17:16:25 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ac_check(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s [number_of_philosophers] [time_to_die] \
[time_to_eat time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (0);
	}
	return (1);
}

static int	is_negative(char *str)
{
	if (str[0] == '-')
	{
		printf("Usage: arguments cannot be negative numbers\n");
		return (1);
	}
	return (0);
}

static int	is_not_digit(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
		{
			printf("Usage: one of the arguments is not a digit\n");
			return (1);
		}
		j++;
	}
	return (0);
}

static int	is_too_large(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (j == 11)
		{
			printf("Usage: arguments cannot be bigger than an int\n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	arg_check(int ac, char **av)
{
	int	i;

	if (!ac_check(ac, av))
		return (0);
	i = 1;
	while (av[i])
	{
		if (is_negative(av[i]) || is_not_digit(av[i]) || is_too_large(av[i]))
			return (0);
		i++;
	}
	return (1);
}

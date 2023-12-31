/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:50:01 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 18:46:21 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* ac_check: checks if the number of arguments is correct
 * the number of arguments must be 5 or 6
 * if the number of arguments is not correct, it prints the usage
 * and returns 0
 * if the number of arguments is correct, it returns 1
 */
static int	ac_check(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s [number_of_philosophers] [time_to_die] \
[time_to_eat time_to_sleep] \
[number_of_times_each_philosopher_must_eat]\n",
			av[0]);
		return (0);
	}
	return (1);
}

/* is_negative: checks if the arguments are negative
 * by comparing the arguments with the minus sign
 * if the arguments are negative, it prints the usage
 * and returns 1
 * if the arguments are not negative, it returns 0
 */
static int	is_negative(char *str)
{
	if (str[0] == '-')
	{
		printf("Usage: arguments cannot be negative numbers\n");
		return (1);
	}
	return (0);
}

/*  is_not_digit: checks if the arguments are not digits 
 *  by comparing the arguments with the digits from 0 to 9
 *  if the arguments are not digits, it prints the usage
 * and returns 1
 * if the arguments are digits, it returns 0
 */
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

/* is_too_large: checks if the arguments are bigger than an int
 * by comparing the length of the arguments with the length of the
 * maximum value of an int
 * also checks if the arguments are bigger than the maximum value of an int
 * by comparing the arguments with the maximum value of an int
 * if the arguments are bigger than an int, it prints the usage
 * and returns 1
 * if the arguments are not bigger than an int, it returns 0
 */
static int	is_too_large(char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str > 10)
	{
		printf("Usage: arguments cannot be bigger than an int\n");
		return (1);
	}
	if (len_str == 10 && ft_strncmp(str, "2147483647", 10) > 0)
	{
		printf("Usage: arguments cannot be bigger than an int\n");
		return (1);
	}
	return (0);
}

/* ac_check: checks if the number of arguments is correct
 * is_negative: checks if the arguments are negative
 * is_not_digit: checks if the arguments are not digits
 * is_too_large: checks if the arguments are bigger than an int
 * arg_check: calls all the functions above and checks if av[1] is
 * between 1 and 500 (the number of philosophers must be between 1 and 500)
 */
int	arg_check(int ac, char **av)
{
	int				i;
	long long int	num;

	if (!ac_check(ac, av))
		return (0);
	num = ft_atoll(av[1]);
	if (num < 0 || num > 500)
	{
		printf("Usage: number of philosophers must be between 1 and 500\n");
		return (0);
	}
	i = 1;
	while (av[i])
	{
		if (is_negative(av[i]) || is_not_digit(av[i]) || is_too_large(av[i]))
			return (0);
		i++;
	}
	return (1);
}

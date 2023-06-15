/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2023/06/15 18:37:47 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo_data(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->num_philos = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		philo->num_meals = ft_atol(av[5]);
	else
		philo->num_meals = -1;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_philos);
	philo->philosopher_mutexes = malloc(sizeof(pthread_mutex_t) * philo->num_philos);
	gettimeofday(&philo->start_time, NULL);
	return (philo);
}

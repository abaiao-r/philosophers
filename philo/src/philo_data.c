/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2023/06/16 18:34:27 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_mutexes(pthread_mutex_t *mutexes, int num_mutexes)
{
	int	i;

	i = 0;
	while (i < num_mutexes)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			printf("Error: Failed to initialize mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_forks(pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: Failed to initialize fork mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_philosophers(pthread_t *philosophers, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->num_philos)
	{
		gettimeofday(&(*philo)[i].start_time, NULL);
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].num_philos = (*philo)->num_philos;
		(*philo)[i].time_to_die = (*philo)->time_to_die;
		(*philo)[i].time_to_eat = (*philo)->time_to_eat;
		(*philo)[i].time_to_sleep = (*philo)->time_to_sleep;
		(*philo)[i].num_meals = (*philo)->num_meals;
		if (pthread_create(&philosophers[i], NULL, routine, &(*philo)[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			return (0);
		}
		i++;
		usleep(900);
	}
	return (1);
}

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
	philo->philosopher_mutexes = malloc(sizeof(pthread_mutex_t)
			* philo->num_philos);
	gettimeofday(&philo->start_time, NULL);
	return (philo);
}

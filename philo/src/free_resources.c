/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/16 16:48:38 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutexes(pthread_mutex_t *mutexes, int num_mutexes)
{
	int	i;

	i = 0;
	while (i < num_mutexes)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	destroy_forks(pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	cleanup(t_philo *philo, pthread_t *philosophers)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
/* 	destroy_mutexes(philo->forks, philo->num_philos);
	destroy_mutexes(philo->philosopher_mutexes, philo->num_philos); */
	free(philosophers);
/* 	free(philo->forks);
	free(philo->philosopher_mutexes); */
	free(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/21 16:36:18 by abaiao-r         ###   ########.fr       */
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

void	cleanup(t_data *data)
{
	if (data)
	{
		if (data->philo)
			free(data->philo);
		if (data->forks)
			destroy_forks(data->forks, data->num_philos);
		if (data->message_mutex)
			destroy_mutexes(data->message_mutex, 1);
		free(data);
	}
}

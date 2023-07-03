/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/03 18:36:26 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		if (data->forks)
			destroy_forks(data->forks, data->num_philos);
		if (data->message_mutex)
			pthread_mutex_destroy(data->message_mutex);
		if (data->death_mutex)
			pthread_mutex_destroy(data->death_mutex);
		if (data->philo)
			free(data->philo);
		if (data->forks)
			free(data->forks);
		if (data->message_mutex)
			free(data->message_mutex);
		if (data->death_mutex)
			free(data->death_mutex);
		free(data);
	}
}

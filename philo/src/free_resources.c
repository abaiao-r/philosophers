/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/05 16:34:50 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_data(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	if (data->message_mutex)
		free(data->message_mutex);
	if (data->end_flag_mutex)
		free(data->end_flag_mutex);
	if (data->meals_eaten_mutex)
		free(data->meals_eaten_mutex);
	if (data->death_mutex)
		free(data->death_mutex);
	free(data);
}

static void	destroy_mutexes(t_data *data)
{
	if (data->message_mutex)
		pthread_mutex_destroy(data->message_mutex);
	if (data->death_mutex)
		pthread_mutex_destroy(data->death_mutex);
	if (data->end_flag_mutex)
		pthread_mutex_destroy(data->end_flag_mutex);
	if (data->meals_eaten_mutex)
		pthread_mutex_destroy(data->meals_eaten_mutex);
}

static void	destroy_forks(pthread_mutex_t *forks, int num_forks)
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
		destroy_mutexes(data);
		free_data(data);
	}
}

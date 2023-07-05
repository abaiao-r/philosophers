/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/05 18:51:57 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* free_data: frees the data struct
** if data exists, it frees the following:
** if philo exists, it frees philo
** if forks exists, it frees forks
** if message_mutex exists, it frees message_mutex
** if end_flag_mutex exists, it frees end_flag_mutex
** if meals_eaten_mutex exists, it frees meals_eaten_mutex
** if death_mutex exists, it frees death_mutex
*/
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

/*  destroy_mutexes: destroys the mutexes
** if the mutex exists, it destroys it
*/
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

/*  destroy_forks: destroys the forks
** by iterating through the forks and destroying them
*/
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

/* cleanup: calls the above functions
** if data exists, it calls the following functions:
** if forks exist, it calls destroy_forks
** it calls destroy_mutexes and free_data
** free_data: frees the data struct
** destroy_mutexes: destroys the mutexes
** destroy_forks: destroys the forks
*/
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

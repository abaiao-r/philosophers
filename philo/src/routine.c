/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/22 22:26:26 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t get_timestamp(time_t start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

void wait_for_all_threads(t_data *data)
{
	while (data->threads_ready < data->num_philos)
		{
			pthread_mutex_lock(data->start_mutex);
			if (data->threads_ready == data->num_philos)
			{
				pthread_mutex_unlock(data->start_mutex);
				break;
			}
			pthread_mutex_unlock(data->start_mutex);
		}
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_for_all_threads(philo->data);
	printf("%ld philosopher %d created\n", get_timestamp(philo->data->start_time), philo->philo_num);
	/* usleep(8000); */
	while (1)
	{
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break;
		if (get_timestamp(philo->last_meal) > philo->data->time_to_die)
		{
			/* pthread_mutex_lock(philo->data->message_mutex); */
			printf("%ld philosopher %d has died\n", get_timestamp(philo->data->start_time), philo->philo_num);
			/* pthread_mutex_unlock(philo->data->message_mutex); */
			break;
		}
		usleep(1000);
	}
	return (NULL);
}

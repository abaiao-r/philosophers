/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/22 16:48:29 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t get_timestamp(time_t start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}


void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	usleep(8000);
	while (1)
	{
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break;
		if (get_timestamp(philo->data->start_time) - philo->data->time_to_die < philo->last_meal)
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

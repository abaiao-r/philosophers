/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/03 19:10:41 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void singular_philo(t_philo *philo)
{
	while (1)
	{
		take_forks(philo);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_lock(philo->data->end_flag_mutex);
		if (philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
	}
}

/* void check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->data->end_flag_mutex);
	if (philo->data->end_flag == 1)
	{
		pthread_mutex_unlock(philo->data->end_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->end_flag_mutex);
	return (0);
} */

void *routine(void *arg)
{
	t_philo *philo;
	time_t	wait;

	philo = (t_philo *)arg;
	printf("%ld philosopher %d was born!\n", get_timestamp(philo->data->start_time), philo->philo_id_num);
	if(philo->data->num_philos == 1)
	{
		singular_philo(philo);
		return (NULL);
	}
	wait = (philo->data->start_time - start_watch()) * 1000;
	if (wait > 0)
		usleep(wait);
	if (philo->philo_id_num % 2 == 0)
		thinking(philo);
	while (1)
	{
		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		}
		take_forks(philo);
		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		}
		eating(philo);
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break;
		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		}
		sleeping(philo);
		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		}
		thinking(philo);
	}
	return (NULL);
}

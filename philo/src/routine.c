/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/04 16:16:34 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void singular_philo(t_philo *philo)
{
	take_forks(philo);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	print_message(philo, "has died");
}

void overwatch(t_data *data)
{
	int i;
	int full;

	while(1)
	{
		if (check_life(data) == 0)
			break;
		if (data->num_meals == -1)
			continue;
		i = 0;
		full = 1;
		while(i < data->num_philos)
		{
			pthread_mutex_lock(data->meals_eaten_mutex);
			if (data->philo[i].meals_eaten < data->num_meals)
				full = 0;
			pthread_mutex_unlock(data->meals_eaten_mutex);
			//if (data->philo[i].meals_eaten >= data->num_meals)
				//break;
			i++;
		}
		if (full == 1)
		{
			pthread_mutex_lock(data->end_flag_mutex);
			data->end_flag = 1;
			pthread_mutex_unlock(data->end_flag_mutex);
			break;
		}

	}
}

void *routine(void *arg)
{
	t_philo *philo;
	time_t	wait;

	philo = (t_philo *)arg;
	//printf("%ld philosopher %d was born!\n", get_timestamp(philo->data->start_time), philo->philo_id_num);
	wait = (philo->data->start_time - start_watch()) * 1000;
	if (wait > 0)
		usleep(wait);
	if(philo->data->num_philos == 1)
	{
		singular_philo(philo);
		return (NULL);
	}
	if (philo->philo_id_num % 2 == 0)
		thinking(philo);
	while (!check_end(philo))
	{
/* 		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		} */
		take_forks(philo);
		/* pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		}  */
		eating(philo);
/* 		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break; */
/* 		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		} */
		sleeping(philo);
/* 		pthread_mutex_lock(philo->data->end_flag_mutex);
		if(philo->data->end_flag == 1 || check_life(philo) == 0)
		{
			pthread_mutex_unlock(philo->data->end_flag_mutex);
			break;
		} */
		thinking(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/27 20:05:53 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t get_timestamp(time_t start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

int check_life(t_philo *philo)
{
	pthread_mutex_lock(philo->data->message_mutex);
	if (get_timestamp(philo->last_meal) > philo->data->time_to_die)
	{
		printf("%ld philosopher %d has died\n", get_timestamp(philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(philo->data->message_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->data->message_mutex);
	return (1);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->message_mutex);
	printf("%ld philosopher %d %s\n", get_timestamp(philo->data->start_time), philo->philo_num, message);
	pthread_mutex_unlock(philo->data->message_mutex);
}

void thinking(t_philo *philo)
{
	time_t time_to_think;

	time_to_think = (philo->data->time_to_die - (get_timestamp(philo->last_meal) - philo->data->time_to_eat)) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_message(philo, "is thinking");
	usleep(time_to_think * 1000);
}



void *routine(void *arg)
{
	t_philo *philo;
	time_t	wait;

	philo = (t_philo *)arg;
	printf("%ld philosopher %d was born!\n", get_timestamp(philo->data->start_time), philo->philo_num);
	wait = (philo->data->start_time - start_watch()) * 1000;
	if (wait > 0)
		usleep(wait);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->last_meal_mutex);
		philo->last_meal = get_timestamp(philo->data->start_time);
		pthread_mutex_unlock(philo->last_meal_mutex);
		print_message(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break;
		if(!check_life(philo))
			break;
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		thinking(philo);
	}
	return (NULL);
}

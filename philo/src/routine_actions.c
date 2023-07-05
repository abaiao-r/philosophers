/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:23:39 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 14:32:13 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	time_t	time_to_think;

	time_to_think = philo->data->time_to_die - (get_timestamp(philo->last_meal) - philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_message(philo, "is thinking");
	usleep(time_to_think * 1000);
}

void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		return ;
	}
	if(pthread_mutex_lock(philo->left_fork) != 0)
		print_message(philo, "left fork mutex lock failed");
	print_message(philo, "has taken a fork");
	if(pthread_mutex_lock(philo->right_fork) != 0)
		print_message(philo, "right fork mutex lock failed");
	print_message(philo, "has taken a fork");
	/* if (philo->philo_id_num % 2 == 0)
	{
		if(pthread_mutex_lock(philo->right_fork) != 0)
			print_message(philo, "right fork mutex lock failed");
		print_message(philo, "has taken a fork");
		if(pthread_mutex_lock(philo->left_fork) != 0)
			print_message(philo, "left fork mutex lock failed");
		print_message(philo, "has taken a fork");
	}
	else
	{
		if(pthread_mutex_lock(philo->left_fork) != 0)
			print_message(philo, "left fork mutex lock failed");
		print_message(philo, "has taken a fork");
		if(pthread_mutex_lock(philo->right_fork) != 0)
			print_message(philo, "right fork mutex lock failed");
		print_message(philo, "has taken a fork");
	} */
}

void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal = get_timestamp(philo->data->start_time);
	pthread_mutex_unlock(philo->data->death_mutex);
	pthread_mutex_lock(philo->data->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->meals_eaten_mutex);
}

void	eating(t_philo *philo)
{
	update_meals(philo);
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	if (philo->philo_id_num % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	/* pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork); */
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

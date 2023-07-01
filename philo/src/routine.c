/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/01 01:11:58 by andrefranci      ###   ########.fr       */
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
	pthread_mutex_lock(philo->data->death_mutex);
	if (get_timestamp(philo->data->start_time) - philo->last_meal > philo->data->time_to_die)
	{
		philo->data->end_flag = 1;
		printf("%ld philosopher %d has died\n", get_timestamp(philo->data->start_time), philo->philo_id_num);
		pthread_mutex_unlock(philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->data->death_mutex);
	return (1);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->message_mutex);
	printf("%ld philosopher %d %s\n", get_timestamp(philo->data->start_time), philo->philo_id_num, message);
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

void	take_forks(t_philo *philo)
{
	if (philo->philo_id_num % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
}
void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal = get_timestamp(philo->data->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->death_mutex);

}

void	eating(t_philo *philo)
{
	print_message(philo, "is eating");
	update_meals(philo);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void *routine(void *arg)
{
	t_philo *philo;
	time_t	wait;

	philo = (t_philo *)arg;
	printf("%ld philosopher %d was born!\n", get_timestamp(philo->data->start_time), philo->philo_id_num);
	wait = (philo->data->start_time - start_watch()) * 1000;
	if (wait > 0)
		usleep(wait);
	if (philo->philo_id_num % 2 == 0)
		thinking(philo);
	while (1)
	{
		if(check_life(philo) == 0 || philo->data->end_flag == 1)
			break;
		take_forks(philo);
		if(check_life(philo) == 0 || philo->data->end_flag == 1)
			break;
		eating(philo);

		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			break;
		if(check_life(philo) == 0 || philo->data->end_flag == 1)
			break;
		sleeping(philo);
		if(check_life(philo) == 0 || philo->data->end_flag == 1)
			break;
		thinking(philo);
	}
	return (NULL);
}

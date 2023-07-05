/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:23:39 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 19:45:05 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*  thinking: it calculates the time to think by subtracting the last meal time
**  from the time to die and dividing by 2
**  if the time to think is less than 0, it sets the time to think to 0
**  if the time to think is 0, it sets the time to think to 1
**  if the time to think is greater than 600, it sets the time to think to 200
**  it prints the thinking message and sleeps for the time to think times 1000
**  because usleep takes microseconds and the time to think is in milliseconds
*/
void	thinking(t_philo *philo)
{
	time_t	time_to_think;

	time_to_think = philo->data->time_to_die - (get_timestamp(philo->last_meal)
			- philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_message(philo, "is thinking");
	usleep(time_to_think * 1000);
}

/*  take_forks: if the number of philosophers is 1, it locks the left fork
**  if the philosopher id number is odd, it locks the left fork and prints the
**  fork message, then it locks the right fork and prints the fork message
**  if the philosopher id number is even, it locks the right fork and prints the
**  fork message, then it locks the left fork and prints the fork message */
void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		return ;
	}
	if (pthread_mutex_lock(philo->left_fork) != 0)
		print_message(philo, "left fork mutex lock failed");
	print_message(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->right_fork) != 0)
		print_message(philo, "right fork mutex lock failed");
	print_message(philo, "has taken a fork");
}

/* update_meals: updates the last meal time
** it locks the death mutex
** it updates the last meal time
** it unlocks the death mutex
** it locks the meals eaten mutex
** it updates the number of meals eaten
** it unlocks the meals eaten mutex */
void	update_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal = get_timestamp(philo->data->start_time);
	pthread_mutex_unlock(philo->data->death_mutex);
	pthread_mutex_lock(philo->data->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->meals_eaten_mutex);
}

/*  eating: it updates the meals eaten, prints the eating message, sleeps for
the time to eat times 1000 because usleep takes microseconds and the time to
eat is in milliseconds, and unlocks the forks */
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
}

/*  sleeping: it prints the sleeping message and sleeps for the
time to sleep times 1000  because usleep takes microseconds and
the time to sleep is in milliseconds */
void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

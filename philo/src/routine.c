/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/05 19:14:13 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*  singular_philo: the routine of the philosopher (thread) if there is only
**  one philosopher
**  it calls take_forks
**  it sleeps for the time to die
**  it unlocks the left fork
**  it prints the death message
*/
void	singular_philo(t_philo *philo)
{
	take_forks(philo);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	print_message(philo, "has died");
}

/*  check_meals_full: checks if the number of meals eaten is equal to the
**  number of meals to eat
**  it iterates through the number of philosophers
**  it locks the meals eaten mutex
**  if the number of meals eaten is less than the number of meals to eat,
**  it unlocks the meals eaten mutex and returns 0
**  if the number of meals eaten is equal to the number of meals to eat,
**  it unlocks the meals eaten mutex and returns 1
*/
static int	check_meals_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(data->meals_eaten_mutex);
		if (data->philo[i].meals_eaten < data->num_meals)
		{
			pthread_mutex_unlock(data->meals_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(data->meals_eaten_mutex);
		i++;
	}
	return (1);
}

/*  set_end_flag: sets the end flag
**  it locks the end flag mutex
**  it sets the end flag to 1
**  it unlocks the end flag mutex
*/
static void	set_end_flag(t_data *data)
{
	pthread_mutex_lock(data->end_flag_mutex);
	data->end_flag = 1;
	pthread_mutex_unlock(data->end_flag_mutex);
}

/*  overwatch: the overwatch thread
**  while the philosophers are alive (check_life), 
**  it checks if the number of meals
**  eaten is equal to the number of meals to eat
**  if it is, it sets the end flag and breaks the loop
*/
void	overwatch(t_data *data)
{
	while (1)
	{
		if (check_life(data) == 0)
			break ;
		if (data->num_meals == -1)
			continue ;
		if (check_meals_full(data))
		{
			set_end_flag(data);
			break ;
		}
	}
}

/*  routine: the routine of the philosopher (thread)
**  it waits for the start time
**  wait is used to make sure all the philosophers start at the same time
**  if the number of philosophers is 1, it calls singular_philo
**  if the philosopher id number is even, it calls thinking
**  because the even numbered philosophers start with the right fork 
** in hand and the odd numbered philosophers start with the left fork 
** in hand (see assign_forks)
**  while the end flag is not set, it calls the following functions:
**  take_forks
**  eating
**  sleeping
**  thinking
**  it returns NULL
*/
void	*routine(void *arg)
{
	t_philo	*philo;
	time_t	wait;

	philo = (t_philo *)arg;
	wait = (philo->data->start_time - start_watch()) * 1000;
	if (wait > 0)
		usleep(wait);
	if (philo->data->num_philos == 1)
	{
		singular_philo(philo);
		return (NULL);
	}
	if (philo->philo_id_num % 2 == 0)
		thinking(philo);
	while (!check_end(philo))
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

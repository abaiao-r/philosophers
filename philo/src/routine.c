/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/07/05 16:17:39 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	singular_philo(t_philo *philo)
{
	take_forks(philo);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	print_message(philo, "has died");
}

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

static void	set_end_flag(t_data *data)
{
	pthread_mutex_lock(data->end_flag_mutex);
	data->end_flag = 1;
	pthread_mutex_unlock(data->end_flag_mutex);
}

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

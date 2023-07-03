/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:19:46 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/03 19:31:18 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death_mutex);
	if (get_timestamp(philo->data->start_time)
		- philo->last_meal > philo->data->time_to_die)
	{
		philo->data->end_flag = 1;
		printf("%ld philosopher %d has died\n",
				get_timestamp(philo->data->start_time),
				philo->philo_id_num);
		pthread_mutex_unlock(philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->data->end_flag_mutex);
	pthread_mutex_unlock(philo->data->death_mutex);
	return (1);
}

void	print_message(t_philo *philo, char *message)
{

	pthread_mutex_lock(philo->data->message_mutex);
	pthread_mutex_lock(philo->data->end_flag_mutex);
	if (philo->data->end_flag == 0)
	{
		printf("%ld philosopher %d %s\n", get_timestamp(philo->data->start_time),
			philo->philo_id_num, message);
	}
	pthread_mutex_unlock(philo->data->end_flag_mutex);
	pthread_mutex_unlock(philo->data->message_mutex);
}

time_t	get_timestamp(time_t start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- start_time);
}

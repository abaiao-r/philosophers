/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:19:46 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 19:22:04 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*  check_life: checks if the philosophers are alive
**  it locks the death mutex
**  it iterates through the number of philosophers
**  if the current time minus the last meal time is greater than or equal to
**  the time to die, it prints the death message
**  in other words if the philosopher has gone without eating more time than
**  the time to die, it prints the death message
**  it locks the end flag mutex
**  it sets the end flag to 1
**  it unlocks the end flag mutex
**  it unlocks the death mutex
**  if the philosopher is alive, it returns 1
**  if the philosopher is dead, it returns 0
*/
int	check_life(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(data->death_mutex);
		if (get_timestamp(data->start_time)
			- data->philo[i].last_meal >= data->time_to_die)
		{
			print_message(&data->philo[i], "has died");
			pthread_mutex_lock(data->end_flag_mutex);
			data->end_flag = 1;
			pthread_mutex_unlock(data->end_flag_mutex);
			pthread_mutex_unlock(data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(data->death_mutex);
		i++;
	}
	return (1);
}

/*  check_end: checks if the end flag is set
**  it locks the end flag mutex
**  if the end flag is set, it unlocks the end flag mutex and returns 1
**  if the end flag is not set, it unlocks the end flag mutex and returns 0
*/
int	check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->data->end_flag_mutex);
	if (philo->data->end_flag == 1)
	{
		pthread_mutex_unlock(philo->data->end_flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->end_flag_mutex);
	return (0);
}

/*  print_message: prints the message
**  it locks the message mutex
**  it prints the timestamp, the philosopher id number and the message
**  it unlocks the message mutex
*/
void	print_message(t_philo *philo, char *message)
{
	if (check_end(philo) == 1)
		return ;
	pthread_mutex_lock(philo->data->message_mutex);
	printf("%ld %d %s\n", get_timestamp(philo->data->start_time),
		philo->philo_id_num + 1, message);
	pthread_mutex_unlock(philo->data->message_mutex);
}

/*  get_timestamp: gets the timestamp
**  it gets the current time minus the start time
**  it returns the timestamp
** start_watch vs get_timestamp	
** start_watch: gets the start time
** get_timestamp: gets the current time minus the start time
*/
time_t	get_timestamp(time_t start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- start_time);
}

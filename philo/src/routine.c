/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:36:23 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/16 18:14:41 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_timestamp(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - philo->start_time.tv_sec) * 1000 +
			(current_time.tv_usec - philo->start_time.tv_usec) / 1000);
}

void	pick_up_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[right_fork]);
		printf("%ld %d has taken the right fork\n", get_timestamp(philo),
				philo->philo_id);
		pthread_mutex_lock(&philo->forks[left_fork]);
		printf("%ld %d has taken the left fork\n", get_timestamp(philo),
				philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[left_fork]);
		printf("%ld %d has taken the left fork\n", get_timestamp(philo),
				philo->philo_id);
		pthread_mutex_lock(&philo->forks[right_fork]);
		printf("%ld %d has taken the right fork\n", get_timestamp(philo),
				philo->philo_id);
	}
}

void	put_down_forks(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&philo->forks[left_fork]);
	printf("%ld %d has released the left fork\n", get_timestamp(philo),
			philo->philo_id);
	pthread_mutex_unlock(&philo->forks[right_fork]);
	printf("%ld %d has released the right fork\n", get_timestamp(philo),
			philo->philo_id);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	size_t			birth_time;
	size_t			death_time;

	philo = (t_philo *)arg;
	birth_time = get_timestamp(philo);
	printf("%ld philosopher[%d] was born!\n", birth_time, philo->philo_id);
	usleep(5000);
	death_time = get_timestamp(philo);
	printf("%ld philospher[%d] has died!\n", death_time, philo->philo_id);
	return (NULL);
}

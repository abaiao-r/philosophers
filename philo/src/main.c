/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/15 21:16:37 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup(t_philo *philo, pthread_t *philosophers)
{
	destroy_mutexes(philo->forks, philo->num_philos);
	destroy_mutexes(philo->philosopher_mutexes, philo->num_philos);
	free(philosophers);
	free(philo->forks);
	free(philo->philosopher_mutexes);
	free(philo);
}

long	get_timestamp(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - philo->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->start_time.tv_usec) / 1000);
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

void	*philosopher(void *arg)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;
	int		meals_eaten;

	philo = (t_philo *)arg;
	left_fork = philo->philo_id - 1;                    // Index of left fork
	right_fork = (philo->philo_id) % philo->num_philos; // Index of right fork
	meals_eaten = 0;                                   
		// Counter to track the number of meals eaten by the philosopher
	while (1)
	{
		// Thinking
		printf("%ld %d is thinking\n", get_timestamp(philo), philo->philo_id);
		// Pick up forks
		pick_up_forks(philo, left_fork, right_fork);
		printf("%ld %d has taken the forks and is now eating\n",
				get_timestamp(philo), philo->philo_id);
		// Eating
		usleep(philo->time_to_eat * 1000);
			// Convert time_to_eat to microseconds
		// Release forks
		put_down_forks(philo, left_fork, right_fork);
		// Increment the meals_eaten counter
		meals_eaten++;
		// Check if the philosopher has eaten the required number of meals
		if (philo->num_meals > 0 && meals_eaten >= philo->num_meals)
		{
			printf("%ld %d has finished all meals\n", get_timestamp(philo),
					philo->philo_id);
			break ; // Exit the loop since the philosopher has finished eating
		}
		// Sleeping
		printf("%ld %d is sleeping\n", get_timestamp(philo), philo->philo_id);
		usleep(philo->time_to_sleep * 1000);
			// Convert time_to_sleep to microseconds
		// Check if the time_to_die condition is met
		if (get_timestamp(philo) - philo->start_time.tv_sec
			* 1000 > philo->time_to_die)
		{
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_id);
			break ; // Exit the loop since the philosopher has died
		}
	}
	return (NULL);
}
void	destroy_mutexes(pthread_mutex_t *mutexes, int num_mutexes)
{
	int	i;

	i = 0;
	while (i < num_mutexes)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

int	create_mutexes(pthread_mutex_t *mutexes, int num_mutexes)
{
	int	i;

	i = 0;
	while (i < num_mutexes)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			printf("Error: Failed to initialize mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_philosophers(pthread_t *philosophers, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		philo->philo_id = i + 1;
		if (pthread_create(&philosophers[i], NULL, philosopher, philo) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_forks(pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	create_forks(pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: Failed to initialize fork mutex\n");
			return (0);
		}
		i++;
	}
	return (1);
}


int	main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	*philosophers;
	int			i;

	if (!arg_check(ac, av))
		return (0);
	philo = init_philo_data(ac, av);
	philosophers = malloc(sizeof(pthread_t) * philo->num_philos);
	if (!philo || !philosophers)
	{
		printf("Error: Memory allocation failed\n");
		cleanup(philo, philosophers);
		return (1);
	}
	if (!create_mutexes(philo->forks, philo->num_philos)
		|| !create_mutexes(philo->philosopher_mutexes, philo->num_philos))
	{
		printf("Failed to initialize mutexes.\n");
		cleanup(philo, philosophers);
		return (1);
	}
	if (!create_philosophers(philosophers, philo))
	{
		printf("Failed to create philosopher threads.\n");
		cleanup(philo, philosophers);
		return (1);
	}
	i = 0;
	while (i < philo->num_philos)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	cleanup(philo, philosophers);
	return (0);
}
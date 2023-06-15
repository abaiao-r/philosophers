/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/15 16:31:41 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	int left_fork = philo->philo_id - 1;                  // Index of left fork
	int right_fork = philo->philo_id % philo->num_philos; // Index of right fork
	int meals_eaten = 0;  // Counter to track the number of meals eaten by the philosopher

		while (1)
		{
		// Thinking
		printf("Philosopher %d is thinking\n", philo->philo_id);

		// Pick up left fork
		pthread_mutex_lock(&forks[left_fork]);
		printf("Philosopher %d has taken the left fork\n", philo->philo_id);

		// Pick up right fork
		pthread_mutex_lock(&forks[right_fork]);
		printf("Philosopher %d has taken the right fork and is now eating\n", philo->philo_id);

		// Eating
		usleep(philo->time_to_eat * 1000);  // Convert time_to_eat to microseconds

		// Release right fork
		pthread_mutex_unlock(&forks[right_fork]);
		printf("Philosopher %d has released the right fork\n", philo->philo_id);

		// Release left fork
		pthread_mutex_unlock(&forks[left_fork]);
		printf("Philosopher %d has released the left fork\n", philo->philo_id);

		// Increment the meals_eaten counter
		meals_eaten++;

		// Check if the philosopher has eaten the required number of meals
		if (philo->num_meals > 0 && meals_eaten >= philo->num_meals) {
			printf("Philosopher %d has finished all meals\n", philo->philo_id);
			break;  // Exit the loop since the philosopher has finished eating
		}

		// Sleeping
		printf("Philosopher %d is sleeping\n", philo->philo_id);
		usleep(philo->time_to_sleep * 1000);  // Convert time_to_sleep to microseconds

		// Check if the time_to_die condition is met
		// TODO: Compare the current time with the time when the philosopher last ate
		// TODO: If the time_to_die condition is met, output log message indicating that the philosopher has died and break from the loop
	}
	return (NULL);
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
	t_philo			*philo;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	int				i;

	if (!arg_check(ac, av))
		return (0);
	philo = init_philo_data(ac, av);
	philosophers = malloc(sizeof(pthread_t) * philo->num_philos);
	forks = malloc(sizeof(pthread_mutex_t) * philo->num_philos);
	if (!philo || !philosophers || !forks)
	{
		printf("Error: Memory allocation failed\n");
		free(philosophers);
		free(forks);
		free(philo);
		return (1);
	}
	if (!create_forks(forks, philo->num_philos))
	{
		printf("Failed to initialize forks.\n");
		free(philosophers);
		free(forks);
		free(philo);
		return (1);
	}
	if (!create_philosophers(philosophers, philo))
	{
		printf("Failed to create philosopher threads.\n");
		destroy_forks(forks, philo->num_philos);
		free(philosophers);
		free(forks);
		free(philo);
		return (1);
	}
	i = 0;
	while (i < philo->num_philos)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	destroy_forks(forks, philo->num_philos);
	free(philosophers);
	free(forks);
	free(philo);
	return (0);
}

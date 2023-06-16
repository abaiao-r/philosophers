/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/16 18:32:23 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	pthread_t	*philosophers;

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
	if (!create_philosophers(philosophers, &philo))
	{
		printf("Failed to create philosopher threads.\n");
		cleanup(philo, philosophers);
		return (1);
	}
	cleanup(philo, philosophers);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/29 15:35:18 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data		*data;
	int i;

	data = NULL;
	if (!arg_check(ac, av))
		return (0);
	data = init_data(ac, av);
	if (!data)
	{
		printf("Error: Memory allocation failed\n");
		cleanup(data);
		return (1);
	}
	if (!create_forks(&data))
	{
		printf("Failed to initialize mutexes.\n");
		cleanup(data);
		return (1);
	}
/* 	if (!create_mutexes(&data))
	{
		printf("Failed to initialize mutexes.\n");
		cleanup(data);
		return (1);
	} */
	if (!create_philosophers(&data))
	{
		printf("Failed to create philosopher threads.\n");
		cleanup(data);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join((data->philo[i].philo_id), NULL);
		i++;
	}
	cleanup(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/07/05 16:34:13 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join((data->philo[i].philo_id), NULL) != 0)
		{
			printf("Error: Failed to join threads\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!arg_check(ac, av))
		return (0);
	data = init_data(ac, av);
	if (!data)
		cleanup(data);
	if (!create_forks(&data))
		cleanup(data);
	if (!create_philosophers(&data))
		cleanup(data);
	if (!join_threads(data))
		cleanup(data);
	cleanup(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2023/06/22 16:47:42 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		printf("Fork %d initialized\n", i + 1);
		i++;
	}
	return (1);
}

int	create_philosophers(t_data **data)
{
	int	i;

	i = 0;
	(*data)->start_time = start_watch();
	while (i < (*data)->num_philos)
	{
		(*data)->philo[i].philo_num = i + 1;
		(*data)->philo[i].meals_eaten = 0;
		(*data)->philo[i].last_meal = (*data)->start_time;
		(*data)->philo[i].data = *data;
		if (pthread_create(&(*data)->philo[i].philo_id, NULL, routine,
				&(*data)->philo[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			return (0);
		}
		usleep(900);
		printf("%ld philosopher %d created\n", get_timestamp((*data)->start_time),i + 1);
		i++;
	}
	return (1);
}
/* start_watch  */
time_t	start_watch(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->num_meals = ft_atol(av[5]);
	else
		data->num_meals = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->start_time = start_watch();
	return (data);
}

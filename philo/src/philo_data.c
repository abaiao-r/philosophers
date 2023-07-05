/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 14:24:55 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_forks(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->num_philos)
	{
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
		{
			printf("Error: Failed to initialize fork mutex\n");
			return (0);
		}
/* 		printf("Fork %d initialized\n", i + 1); */
		i++;
	}
	return (1);
}

void	assign_forks(t_philo *philo)
{
 	if (philo->data->num_philos == 1)
	{
		philo->left_fork = &philo->data->forks[0];
		philo->right_fork = &philo->data->forks[0];
		printf("Philosopher %d left fork: %p\n", philo->philo_id_num + 1, philo->left_fork);
		printf("Philosopher %d right fork: %p\n", philo->philo_id_num + 1, philo->right_fork);
		return ;
	} 
	if(philo->philo_id_num % 2)
	{
		philo->left_fork = &philo->data->forks[philo->philo_id_num];
		philo->right_fork = &philo->data->forks[(philo->philo_id_num + 1) % philo->data->num_philos];
	}
	else
	{
		philo->left_fork = &philo->data->forks[(philo->philo_id_num + 1) % philo->data->num_philos];
		philo->right_fork = &philo->data->forks[philo->philo_id_num];
	}

	/* if (philo->philo_id_num == 1)
	{
		philo->left_fork = &philo->data->forks[philo->philo_id_num];
		philo->right_fork = &philo->data->forks[philo->data->num_philos];
	}
	else
	{
		philo->left_fork = &philo->data->forks[philo->philo_id_num];
		philo->right_fork = &philo->data->forks[philo->philo_id_num - 1];
	} */
/* 	printf("Philosopher %d left fork: %p\n", philo->philo_id_num + 1, philo->left_fork);
	printf("Philosopher %d right fork: %p\n", philo->philo_id_num + 1, philo->right_fork); */
}




int	create_philosophers(t_data **data)
{
	int	i;

	i = 0;
	(*data)->start_time = start_watch() + ((*data)->num_philos * 2);
	while (i < (*data)->num_philos)
	{
		(*data)->philo[i].philo_id_num = i;
		(*data)->philo[i].meals_eaten = 0;
		(*data)->philo[i].last_meal = (*data)->start_time;
		(*data)->philo[i].data = *data;
		assign_forks(&((*data)->philo[i]));
		if (pthread_create(&(*data)->philo[i].philo_id, NULL, routine,
				&(*data)->philo[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread\n");
			return (0);
		}
		i++;
		usleep(900);
	}
	if ((*data)->num_philos > 1)
		overwatch(*data);
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
	data->end_flag = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->message_mutex = malloc(sizeof(pthread_mutex_t));
	data->death_mutex = malloc(sizeof(pthread_mutex_t));
	data->end_flag_mutex = malloc(sizeof(pthread_mutex_t));
	data->meals_eaten_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->message_mutex, NULL);
	pthread_mutex_init(data->death_mutex, NULL);
	pthread_mutex_init(data->end_flag_mutex, NULL);
	pthread_mutex_init(data->meals_eaten_mutex, NULL);
	return (data);
}

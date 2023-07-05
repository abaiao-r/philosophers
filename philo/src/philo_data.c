/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 19:56:05 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*  create_forks: creates the forks (mutexes)
**  it iterates through the number of philosophers
**  it initializes the forks
**  it returns 1 if the forks were created successfully
**  it returns 0 if the forks were not created successfully
*/
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
		i++;
	}
	return (1);
}

/*  assign_forks: assigns the forks to the philosophers
**  if the number of philosophers is 1, it assigns the same fork to both
**  if the philosopher id number is odd, it assigns the left fork to the
**  philosopher id number and the right fork to the philosopher id number + 1
**  if the philosopher id number is even, it assigns the left fork to the
**  philosopher id number + 1 and the right fork to the philosopher id number
*/
void	assign_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		philo->left_fork = &philo->data->forks[0];
		philo->right_fork = &philo->data->forks[0];
		return ;
	}
	if (philo->philo_id_num % 2)
	{
		philo->left_fork = &philo->data->forks[philo->philo_id_num];
		philo->right_fork = &philo->data->forks[(philo->philo_id_num + 1)
			% philo->data->num_philos];
	}
	else
	{
		philo->left_fork = &philo->data->forks[(philo->philo_id_num + 1)
			% philo->data->num_philos];
		philo->right_fork = &philo->data->forks[philo->philo_id_num];
	}
}

/*  create_philosophers: creates the philosophers (threads)
**  it iterates through the number of philosophers
**  it assigns the values to the philosopher struct
**  it assigns the forks to the philosopher struct
**  it creates the philosopher thread
**  it returns 1 if the thread was created successfully
**  it returns 0 if the thread was not created successfully
** usleep(900) is used to avoid the threads from being created at the same time
** if the number of philosophers is greater than 1, it calls overwatch
** overwatch is a function that checks if the philosophers are alive
** if the philosophers are not alive, it ends the philosophers (threads)
*/
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

/* start_watch: starts the timer
** it gets the current time
** it returns the current time in milliseconds
*/
time_t	start_watch(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
}

/* init_data: initializes the data struct
** it allocates memory for the data struct
** it assigns the values from the arguments to the data struct
** it allocates memory for the philo struct
** it allocates memory for the forks
** it initializes the mutexes
** it returns the data struct
*/
t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->num_philos = ft_atoll(av[1]);
	data->time_to_die = ft_atoll(av[2]);
	data->time_to_eat = ft_atoll(av[3]);
	data->time_to_sleep = ft_atoll(av[4]);
	if (ac == 6)
		data->num_meals = ft_atoll(av[5]);
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

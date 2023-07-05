/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/07/05 19:48:11 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* join_threads: joins the threads
** pthread_join: waits for the thread to terminate
** it iterates through the number of philosophers
** it joins the thread
** it returns 1 if the threads were joined successfully
** it returns 0 if the threads were not joined successfully
** is usefull to check if the threads were joined successfully
** because if they were not joined successfully, the program will not end
*/
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

/*  main: the main function
**  it checks the arguments
**  it initializes the data
**  it creates the forks
**  it creates the philosophers
**  it joins the threads
**  it cleans up the data
*/
int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!arg_check(ac, av))
		return (0);
	data = init_data(ac, av);
	if (!data)
	{
		printf("Error: Failed to initialize data\n");
		cleanup(data);
		return (0);
	}
	if (!create_forks(&data))
		cleanup(data);
	if (!create_philosophers(&data))
		cleanup(data);
	if (!join_threads(data))
		cleanup(data);
	cleanup(data);
	return (0);
}

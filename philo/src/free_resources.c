/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:29:58 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/15 21:31:12 by abaiao-r         ###   ########.fr       */
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

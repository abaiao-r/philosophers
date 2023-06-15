/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:12:41 by codespace         #+#    #+#             */
/*   Updated: 2023/06/15 21:05:36 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				philo_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philosopher_mutexes;
	struct timeval	start_time;
}					t_philo;

void cleanup(t_philo *philo, pthread_t *philosophers);
t_philo *init_philo_data(int ac, char **av);
long get_timestamp(t_philo *philo);
void pick_up_forks(t_philo *philo, int left_fork, int right_fork);
void put_down_forks(t_philo *philo, int left_fork, int right_fork);
void *philosopher(void *arg);
void destroy_mutexes(pthread_mutex_t *mutexes, int num_mutexes);
int create_mutexes(pthread_mutex_t *mutexes, int num_mutexes);
int create_philosophers(pthread_t *philosophers, t_philo *philo);
void destroy_forks(pthread_mutex_t *forks, int num_forks);
int create_forks(pthread_mutex_t *forks, int num_forks);
void check_deadlock(t_philo *philo);
void display_status(t_philo *philo);
int check_meals_completed(t_philo *philo);
void update_timestamp(t_philo *philo);

/* arg_check.c */
int					arg_check(int ac, char **av);

/* free_resources.c */
void				cleanup(t_philo *philo, pthread_t *philosophers);

/* philo_data.c */
t_philo				*init_philo_data(int ac, char **av);

/* routine.c */


/* utils.c */
int					ft_isdigit(char c);
long				ft_atol(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

#endif
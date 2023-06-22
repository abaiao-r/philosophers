/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:12:41 by codespace         #+#    #+#             */
/*   Updated: 2023/06/22 16:47:54 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philo
{
	pthread_t		philo_id;
	int				philo_num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals_eaten;
	pthread_mutex_t	*last_meal_mutex;
	time_t			last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*message_mutex;
	time_t			start_time;
}					t_data;

/* arg_check.c */
int					arg_check(int ac, char **av);

/* free_resources.c */
void	destroy_mutexes(pthread_mutex_t *mutexes,
						int num_mutexes);
void				destroy_forks(pthread_mutex_t *forks, int num_forks);
void				cleanup(t_data *data);

/* philo_data.c */
int					create_forks(pthread_mutex_t *forks, int num_forks);
time_t				start_watch(void);
int					create_philosophers(t_data **data);
t_data				*init_data(int ac, char **av);

/* routine.c */
time_t				get_timestamp(time_t start_time);
void				*routine(void *arg);

/* create_philosophers.c */

/* utils.c */
int					ft_isdigit(char c);
long				ft_atol(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

#endif
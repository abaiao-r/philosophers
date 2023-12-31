/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:12:41 by codespace         #+#    #+#             */
/*   Updated: 2023/07/05 18:36:00 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		philo_id;
	int				philo_id_num;
	int				meals_eaten;
	time_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_meals;
	int				end_flag;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*message_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*end_flag_mutex;
	pthread_mutex_t	*meals_eaten_mutex;
	time_t			start_time;
}					t_data;

/* arg_check.c */
int					arg_check(int ac, char **av);

/* free_resources.c */
void				cleanup(t_data *data);

/* philo_data.c */
int					create_forks(t_data **data);
void				assign_forks(t_philo *philo);
time_t				start_watch(void);
int					create_philosophers(t_data **data);
t_data				*init_data(int ac, char **av);

/* routine.c */

void				overwatch(t_data *data);
void				*routine(void *arg);

/* routine_actions */
void				thinking(t_philo *philo);
void				take_forks(t_philo *philo);
void				update_meals(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);

/* routine_utils.c */
void				singular_philo(t_philo *philo);
int					check_life(t_data *data);
int					check_end(t_philo *philo);
void				print_message(t_philo *philo, char *message);
time_t				get_timestamp(time_t start_time);

/* utils.c */
size_t				ft_strlen(const char *s);
int					ft_isdigit(char c);
long long int		ft_atoll(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

/* utils_2.c */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
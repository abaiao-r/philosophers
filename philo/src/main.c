/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/12 17:20:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(const char *nptr)
{
	long	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10;
		result = result + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

t_philo *init_philo_data(int ac, char **av)
{
    t_philo *philo;

    philo = malloc(sizeof (t_philo));
    philo->num_philos = ft_atol(av[1]);
    philo->time_to_die = ft_atol(av[2]);
    philo->time_to_eat = ft_atol(av[3]);
    philo->time_to_sleep = ft_atol(av[4]);
    if(ac == 6 )
        philo->num_meals = ft_atol(av[5]);
    else
        philo->num_meals = -1;
    return(philo);
}


void	ft_bzero(void*s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int arg_check(int ac, char ** av)
{
    int i;
    int j;
    
    if (ac < 5 || ac > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
        return (0);
    }
    
    i = 0;
    while(av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (j == 0)
            {
                if(av[i][j] == '-')
                {
                    printf("Usage: arguments can not be negative number\n");
                    return(0);
                }
            }
            if(!ft_isdigit(av[i][j]))
            {
                printf("Usage: one of the arguments is not a digit\n");
                return(0);
            }
            if (j == 11)
            {
                printf("Usage: arguments can not be bigger than an int\n");
                return(0);   
            }
            j++;
        }
        i++;
    }
    return (1);
}

int main(int ac, char **av)
{
    t_philo *philo;
    
    if(!arg_check(ac, av))
        return(0);
    
    philo = init_philo_data(ac, av);

    


    free(philo);
    return(0);
}

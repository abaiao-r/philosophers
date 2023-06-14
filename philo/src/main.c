/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:25 by codespace         #+#    #+#             */
/*   Updated: 2023/06/14 21:09:59 by andrefranci      ###   ########.fr       */
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


int main(int ac, char **av)
{
    t_philo *philo;
    
    if(!arg_check(ac, av))
        return(0);
    
    philo = init_philo_data(ac, av);

    


    free(philo);
    return(0);
}

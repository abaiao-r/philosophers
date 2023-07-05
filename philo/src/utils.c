/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:07:08 by andrefranci       #+#    #+#             */
/*   Updated: 2023/07/05 19:05:44 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*  ft_strlen: returns the length of the string
 *  by iterating through the string until it reaches the null terminator
 *  it returns the length of the string
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*  ft_isdigit: checks if the character is a digit
 *  by comparing the character with the digits from 0 to 9
 *  if the character is a digit, it returns 1
 * if the character is not a digit, it returns 0
 */
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*  ft_atoll: converts the initial portion of the string pointed to by nptr to
 *  long long int representation
 *  ft_atoll returns the converted value
 *  if the string does not contain a valid integer, ft_atoll returns zero
 *  if the converted value is out of the range of representable values by a
 *  long long int, it returns LONG_MAX or LONG_MIN
 */
long long int	ft_atoll(const char *nptr)
{
	long long int	i;
	int				sign;
	int				result;

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

/*  ft_bzero: writes n zeroed bytes to the string s
 *  if n is zero, ft_bzero does nothing
 *  ft_bzero returns nothing
 */
void	ft_bzero(void *s, size_t n)
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

/*  ft_calloc: allocates memory for an array of nmemb elements of size bytes
 *  and returns a pointer to the allocated memory
 *  the memory is set to zero
 *  if nmemb or size is 0, then ft_calloc returns NULL
 *  if malloc fails, then ft_calloc returns NULL
 * 		- malloc is called with the size of nmemb * size
 * 		- if malloc fails, then ft_calloc returns NULL
 * ft_bzero is called with the pointer to the allocated memory and the size of
 * nmemb * size
 * 		- ft_bzero sets the memory to zero
 * ft_calloc returns the pointer to the allocated memory
 */
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

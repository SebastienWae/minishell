/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:08:22 by seb               #+#    #+#             */
/*   Updated: 2022/02/28 15:05:19 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\t'
		|| c == '\v'
		|| c == '\r'
		|| c == '\f'
		|| c == '\n')
		return (1);
	return (0);
}

/*
 * Function: ft_atoi
 * --------------------
 * Converts the initial portion of the string pointed to by str to int
 * representation.
 *
 * str: the string to convert.
 *
 * Return: The integer respresenting the string.
 */
int	ft_atoi(const char *str)
{
	unsigned long long	r;
	int					sig;
	int					i;

	r = 0;
	sig = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sig = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		r = (r * 10) + (str[i++] - '0');
		if (r > (unsigned long long)(0x7fffffffffffffffLL) + 1 && sig == -1)
			return (0);
		if (r > 0x7fffffffffffffffLL && sig == 1)
			return (-1);
	}
	return (r * sig);
}

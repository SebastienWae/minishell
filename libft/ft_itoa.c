/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:15:52 by seb               #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_int_size(int n)
{
	size_t			size;
	unsigned int	nbr;

	size = 1;
	if (n < 0)
	{
		nbr = -n;
		size++;
	}
	else
		nbr = n;
	while (nbr >= 10)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

/*
 * Function: ft_itoa
 * --------------------
 * Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 *
 * n: the integer to convert.
 *
 * Return: The string representing the integer.
 * NULL if the allocation fails.
 */
char	*ft_itoa(int n)
{
	char			*str;
	size_t			size;
	unsigned int	nbr;

	size = get_int_size(n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = 0;
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (size > 0)
	{
		str[--size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

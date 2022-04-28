/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:58:12 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_strncmp
 * --------------------
 * Compare lexicographically not more than n char of the null-terminated
 * strings s1 and s2.
 *
 * s1: the first string to compare.
 * s2: the second string to compare.
 * size: the maximum number of char to compare.
 * 
 * Return: An integer greater than, equal to, or less than 0, according as
 * the string s1 is greater than, equal to, or less than the string s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

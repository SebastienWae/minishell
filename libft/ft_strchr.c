/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:56:11 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_strchr
 * --------------------
 * Locates the first occurrence of c (converted to a char) * in the string
 * pointed to by s.  The terminating null character is considered to be part
 * of the string; therefore if c is `\0', the functions locate the
 * terminating `\0'.
 *
 * s: The string to search in.
 * c: the char to search for.
 * 
 * Return: Pointer to the located char or NULL if the char does not appear in
 * the string.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

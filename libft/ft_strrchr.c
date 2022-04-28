/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:35:45 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Function: ft_strrchr
 * --------------------
 * locates the first occurrence of c (converted to a char) in the string pointed
 * to by s. The terminating null character is considered to be part * of the
 * string; therefore if c is `\0', the functions locate the terminating `\0'.
 *
 * s: the string to search in
 * c: the char to search fo
 * 
 * Return: A pointer to the located character.
 * NULL if the character does not appear in the string. 
 */
char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (s[s_len] == (char)c)
			return ((char *)&s[s_len]);
		s_len--;
	}
	return (NULL);
}

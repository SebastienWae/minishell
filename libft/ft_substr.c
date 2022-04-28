/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:35:57 by seb               #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* Function: ft_substr
 * --------------------
 * Allocates (with malloc(3)) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 *
 * s: The string from which to create the substring.
 * start: The start index of the substring in the string ’s’.
 * len: The maximum length of the substring.
 * 
 * Return: The substring.
 * NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*final;

	if (s)
	{
		if (start >= ft_strlen(s) || len == 0 || ft_strlen(s) == 0)
			return (ft_strdup(""));
		i = 0;
		while (i < len && s[i + start])
			i++;
		final = (char *)malloc((sizeof(char) * i) + 1);
		if (!(final))
			return (NULL);
		j = 0;
		while (j < i)
		{
			final[j] = s[start + j];
			j++;
		}
		final[j] = 0;
		return (final);
	}
	return (NULL);
}

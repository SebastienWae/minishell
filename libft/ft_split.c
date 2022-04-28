/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:29:04 by seb               #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_split_n(const char *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s)
				s++;
			n++;
		}
	}
	return (n);
}

/*
 * Function: ft_split
 * --------------------
 * Allocates (with malloc(3)) and returns an array of strings
 * obtained by splitting ’s’ using the character ’c’ as a delimiter.
 * The array must end with a NULL pointer. 
 *
 * s: The string to be split.
 * c: The delimiter character.
 *
 * Return: The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	strs_i;
	char	**strs;

	if (!s)
		return (NULL);
	strs = ft_calloc(get_split_n(s, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	strs_i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (*s != c && *s && ++i)
				s++;
			strs[strs_i] = ft_calloc(i + 1, sizeof(char));
			ft_strlcpy(strs[strs_i++], s - i, i + 1);
		}
	}
	strs[strs_i] = NULL;
	return (strs);
}

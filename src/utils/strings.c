/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/11 15:43:38 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i] != '\0' && str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == str2[i])
			i++;
	}
	if (str1[i] == '\0' && str2[i] != '\0')
		return (-1);
	if (str1[i] != '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strncpy(char *src, size_t index, size_t end)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * (end - index + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (index < end)
	{
		dest[i] = src[index];
		i++;
		index ++;
	}
	dest[i] = '\0';
	return (dest);
}

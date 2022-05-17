/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/17 13:44:39 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

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
		index++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_sep(const char *s1, const char *s2, const char *sep)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(s1, sep);
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

char	*ft_strappend(const char *s1, const char c)
{
	char	*str;
	int		len;

	if (s1)
		len = ft_strlen(s1);
	else
		len = 0;
	str = malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len + 1);
	str[len] = c;
	str[len + 1] = 0;
	return (str);
}

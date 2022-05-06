/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:41:32 by jeulliot          #+#    #+#             */
/*   Updated: 2022/03/03 13:41:35 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strcat(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i ++;
	}
	if (s2 != NULL)
	{
		while (s2[j] != '\0')
		{
			dest[i] = s2[j];
			i ++;
			j ++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if ((dest == NULL || s1 == NULL) && s2 != NULL)
		return (NULL);
	dest = ft_strcat(dest, s1, s2);
	if (dest[0] == '\0')
	{
		free (dest);
		return (NULL);
	}
	return (dest);
}

int	ft_is_a_line(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_charge_buffer(int fd, char *buf, char *tmp, char *next)
{
	int	r;

	r = -1;
	while (r != 0)
	{
		next = tmp;
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[r] = '\0';
		if (next == NULL)
		{
			next = malloc(sizeof(char));
			next[0] = '\0';
		}
		tmp = ft_strjoin(next, buf);
		free (next);
		if (ft_is_a_line(tmp) == 1)
			break ;
	}
	free (buf);
	return (tmp);
}

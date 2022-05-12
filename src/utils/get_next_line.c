/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:41:11 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/12 16:32:05 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdlib.h>
#include <libft.h>

char	*ft_copy_temp(char *str)
{
	size_t	j;
	size_t	i;
	char	*end;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i ++;
	if (i == ft_strlen(str))
	{
		free(str);
		return (NULL);
	}
	i ++;
	end = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (end == NULL)
		return (NULL);
	while (str[i] != '\0')
		end[j++] = str[i++];
	end[j] = '\0';
	free(str);
	return (end);
}

char	*ft_fill_line(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i ++;
	if (tmp[0] == '\0')
		return (NULL);
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		line[i] = tmp[i];
		i ++;
	}
	if (tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*line;
	char		*next;
	char		*buf;

	next = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	tmp = ft_charge_buffer(fd, buf, tmp, next);
	if (tmp == NULL)
		return (NULL);
	line = ft_fill_line(tmp);
	tmp = ft_copy_temp(tmp);
	return (line);
}

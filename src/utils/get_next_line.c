/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:41:11 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/18 13:35:12 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <utils.h>

char	*get_first_line(char **line_buf)
{
	char	*line;
	char	*tmp_buf;
	char	*end_ptr;

	if (!line_buf)
		return (NULL);
	end_ptr = ft_strchr(*line_buf, (int) '\n');
	if (end_ptr)
	{
		line = ft_substr(*line_buf, 0, (end_ptr - *line_buf) + 1);
		tmp_buf = ft_strdup(end_ptr + 1);
		free(*line_buf);
		*line_buf = tmp_buf;
	}
	else
	{
		line = ft_strdup(*line_buf);
		free(*line_buf);
		*line_buf = 0;
	}
	return (line);
}

void	read_file(int fd, char **line_buf)
{
	int		b;
	char	buf[BUFFER_SIZE + 1];
	char	*line;

	b = 1;
	while (b && !ft_strchr(*line_buf, (int) '\n'))
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b < 0)
			break ;
		buf[b] = 0;
		line = ft_strjoin(*line_buf, (char *)buf);
		free(*line_buf);
		*line_buf = line;
	}
}

char	*get_next_line(int fd)
{
	static char	*line_buf;

	if (!line_buf)
	{
		line_buf = malloc(sizeof(char));
		if (!line_buf)
			return (NULL);
		*line_buf = 0;
	}
	read_file(fd, &line_buf);
	if (line_buf && !*line_buf)
	{
		free(line_buf);
		line_buf = 0;
		return (NULL);
	}
	return (get_first_line(&line_buf));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:18 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/16 17:09:25 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <sys/fcntl.h>
#include <utils.h>
#include <errno.h>
#include <string.h>

void	ft_close_fd(t_minishell shell, int fd_in, int fd_out)
{
	dup2(shell.saved_stdout, 1);
	dup2(shell.saved_stdin, 0);
	close(fd_out);
	close(fd_in);
}

void	ft_close_saved_fd(t_minishell shell)
{
	close(shell.saved_stdout);
	close(shell.saved_stdin);
}

t_fd_in_out	ft_init_fd(void)
{
	t_fd_in_out		fd;

	fd.out = dup(1);
	fd.in = dup(0);
	return (fd);
}

void	ft_fd_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

int	ft_heredoc_in(t_redir *redir)
{
	char	*input;
	char	*line;
	int		fd_tmp;

	input = "";
	ft_putstr_fd("\U0001F984 ", 2);
	line = get_next_line(STDIN_FILENO);
	while (1)
	{		
		ft_putstr_fd("\U0001F984 ", 2);
		input = ft_strjoin(input, line);
		line = NULL;
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, ft_strjoin(redir->target, "\n")) == 0)
			break ;
	}
	fd_tmp = open("tmp/fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_tmp == -1)
		ft_putstr_fd("Cannot create tmp file\n", 2);
	write(fd_tmp, input, ft_strlen(input));
	free(line);
	free(input);
	return (fd_tmp);
}

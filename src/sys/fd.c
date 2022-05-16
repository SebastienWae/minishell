/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:16:34 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/16 14:07:21 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <utils.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <utils.h>
#include <fcntl.h>
#include <sys.h>
#include <errno.h>

/* TO DO :
close fd if necessary
expand in heredoc
*/
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
	return(fd_tmp);
}

static int	redir_in(t_redir *redir)
{
	static char	*redir_types[] = {"NONE", "IN", "OUT", "HEREDOC", "APPEND"};
	int fd;
	int	fd_tmp;

	if (ft_strcmp(redir_types[redir->type], "HEREDOC") == 0)
	{
		fd_tmp = ft_heredoc_in(redir);
		close (fd_tmp);		
		fd = open("tmp/fd_tmp", O_RDWR, 0644);
		if (fd == -1)
			ft_putstr_fd("Cannot read tmp file\n", 2);
	}
	else if (ft_strcmp(redir_types[redir->type], "IN") == 0)
	{
		fd = open(redir->target, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
		}
	}
	else 
		fd = dup(0);	
	return (fd);
}
static int	redir_out(t_redir *redir)
{
	static char	*redir_types[] = {"NONE", "IN", "OUT", "HEREDOC", "APPEND"};
	int	fd;
	
	if (ft_strcmp(redir_types[redir->type], "OUT") == 0)
	{
		fd = open(redir->target, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
		}
	}
	else if (ft_strcmp(redir_types[redir->type], "APPEND") == 0)
	{
		fd = open(redir->target, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
		}
	}
	else 
		fd = dup(1);
	return (fd);
}

t_fd_in_out	ft_fd_manager(t_cmd *cmd, int choice)
{
	t_fd_in_out		fd;
	int	fd_tmp;	
	t_list	*in;
	t_list	*out;

	in = cmd->in;
	out = cmd->out;
	if (choice == 1 || choice == 0)
	{
		while (in)
		{		
			fd_tmp = redir_in(in->content);
			fd.in = dup(fd_tmp);
			if (in->next)
				close(fd.in);
			close(fd_tmp);
			in = in->next;
		}
		dup2(fd.in, STDIN_FILENO);	
	}
	if (choice == 2 || choice == 0)
	{
		while (out)
		{		
			fd_tmp = redir_out(out->content);
			fd.out = dup(fd_tmp);
			if (out->next)
				close(fd.out);
			close(fd_tmp);
			out = out->next;
		}
		dup2(fd.out, STDOUT_FILENO);
	}
	return (fd);
}

t_fd_in_out	ft_init_fd(void)
{
	t_fd_in_out		fd;

	fd.out = dup(1);
	fd.in = dup(0);
	return (fd);
}

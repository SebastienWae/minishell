/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:16:34 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/19 17:53:14 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <string.h>
#include <sys.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <utils.h>

static int	redir_in(t_redir *redir, t_minishell shell)
{
	int	fd;
	int	fd_tmp;

	if (redir->type == P_RT_HEREDOC || redir->type == P_RT_HEREDOC_QUOTED)
	{
		fd_tmp = ft_heredoc_in(redir, shell);
		close(fd_tmp);
		fd = open("/tmp/minishell_fd_tmp", O_RDWR, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(": Heredoc : Cannot read tmp file. Abort\n", 2);
		}
	}
	else if (redir->type == P_RT_IN)
	{
		fd = open(redir->target, O_RDONLY);
		if (fd == -1)
			ft_fd_error(redir->target);
	}
	else
		fd = dup(0);
	return (fd);
}

static int	redir_out(t_redir *redir)
{
	int	fd;

	if (redir->type == P_RT_OUT)
	{
		fd = open(redir->target, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_fd_error(redir->target);
	}
	else if (redir->type == P_RT_APPEND)
	{
		fd = open(redir->target, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_fd_error(redir->target);
	}
	else
		fd = dup(1);
	return (fd);
}

static int	ft_infile_scan(t_cmd *cmd, t_minishell shell)
{
	int			fd_in;
	int			fd_tmp;
	t_list		*in;

	in = cmd->in;
	fd_in = 0;
	while (in)
	{
		fd_tmp = redir_in(in->content, shell);
		if (fd_tmp == -1)
		{
			close(fd_tmp);
			fd_in = -1;
			return (fd_in);
		}
		fd_in = dup(fd_tmp);
		if (in->next)
			close(fd_in);
		close(fd_tmp);
		in = in->next;
	}
	dup2(fd_in, STDIN_FILENO);
	return (fd_in);
}

static int	ft_outfile_scan(t_cmd *cmd)
{
	int			fd_out;
	int			fd_tmp;
	t_list		*out;

	out = cmd->out;
	fd_out = 1;
	while (out)
	{
		fd_tmp = redir_out(out->content);
		fd_out = dup(fd_tmp);
		if (out->next)
			close(fd_out);
		close(fd_tmp);
		out = out->next;
	}
	dup2(fd_out, STDOUT_FILENO);
	return (fd_out);
}

t_fd_in_out	ft_fd_manager(t_cmd *cmd, int choice, t_minishell shell)
{
	t_fd_in_out	fd;

	if (choice == 1 || choice == 0)
		fd.in = ft_infile_scan(cmd, shell);
	if (choice == 2 || choice == 0)
		fd.out = ft_outfile_scan(cmd);
	return (fd);
}

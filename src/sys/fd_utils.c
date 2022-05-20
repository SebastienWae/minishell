/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:18 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 12:29:29 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <expand.h>
#include <libft.h>
#include <minishell.h>
#include <signal.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys.h>
#include <sys/signal.h>
#include <unistd.h>
#include <utils.h>

void	ft_reset_fd(t_minishell shell)
{
	dup2(shell.saved_stdout, 1);
	dup2(shell.saved_stdin, 0);
}

void	ft_close_saved_fd(t_minishell shell)
{
	close(shell.saved_stdout);
	close(shell.saved_stdin);
}

void	ft_fd_error(char *cmd)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	ft_sig_hd_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
		return ;
}

int	ft_heredoc_in(t_redir *redir, t_minishell shell)
{
	char		*input;
	char		*line;
	char		*word;
	int			fd_tmp;
	t_expand	*exp;

	input = "";
	word = ft_strjoin(redir->target, "\n");
	fd_tmp = open("/tmp/minishell_fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (signal(SIGINT, &ft_sig_hd_handle) == SIG_ERR
		|| signal(SIGQUIT, &ft_sig_hd_handle) == SIG_ERR)
		return (fd_tmp);
	ft_putstr_fd("\U0001F984 ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line || ft_strcmp(line, word) == 0)
	{
		if (line)
			free(line);
		return (fd_tmp);
	}
	while (1)
	{		
		input = ft_strjoin(input, line);
		free(line);
		ft_putstr_fd("\U0001F984 ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(input);
			free(word);
			return (fd_tmp);
		}
		if (ft_strcmp(line, word) == 0)
			break ;
	}
	if (redir->type == P_RT_HEREDOC_QUOTED)
		exp = expand(input, 0, &shell);
	else
		exp = expand(input, E_FORCE_VARIABLE, &shell);
	if (fd_tmp == -1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("Cannot create tmp file\n", 2);
	}
	ft_putstr_fd(exp->result, fd_tmp);
	free(line);
	free(input);
	free(exp->result);
	free(word);
	return (fd_tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:18 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 14:12:51 by seb              ###   ########.fr       */
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

void	ft_hd_error(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Cannot create tmp file\n", 2);
}

void	ft_free_hd_var(t_heredoc hd)
{
	free(hd.line);
	free(hd.input);
	free(hd.exp->result);
	free(hd.word);
}

int	ft_heredoc_in(t_redir *redir, t_minishell shell)
{
	t_heredoc	hd;

	hd.input = "";
	hd.word = ft_strjoin(redir->target, "\n");
	hd.fd_tmp = open("/tmp/minishell_fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (signal(SIGINT, &ft_sig_hd_handle) == SIG_ERR
		|| signal(SIGQUIT, &ft_sig_hd_handle) == SIG_ERR)
		return (hd.fd_tmp);
	ft_putstr_fd("\U0001F984 ", 2);
	hd.line = get_next_line(STDIN_FILENO);
	if (!hd.line || ft_strcmp(hd.line, hd.word) == 0)
	{
		if (hd.line)
			free(hd.line);
		else 
			free(hd.word);
		return (hd.fd_tmp);
	}
	while (1)
	{		
		hd.input = ft_strjoin(hd.input, hd.line);
		free(hd.line);
		ft_putstr_fd("\U0001F984 ", 2);
		hd.line = get_next_line(STDIN_FILENO);
		if (!hd.line)
		{
			free(hd.input);
			free(hd.word);
			return (hd.fd_tmp);
		}
		if (ft_strcmp(hd.line, hd.word) == 0)
			break ;
	}
	if (redir->type == P_RT_HEREDOC_QUOTED)
		hd.exp = expand(hd.input, 0, &shell);
	else
		hd.exp = expand(hd.input, E_FORCE_VAR, &shell);
	if (hd.fd_tmp == -1)
		ft_hd_error();
	ft_putstr_fd(hd.exp->result, hd.fd_tmp);
	ft_free_hd_var(hd);
	return (hd.fd_tmp);
}

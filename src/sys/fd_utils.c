/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:18 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/21 07:50:38 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/fcntl.h>
#include <sys.h>

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

static t_heredoc	ft_init_heredoc(t_redir *redir)
{
	t_heredoc	hd;

	hd.input = "";
	hd.word = ft_strjoin(redir->target, "\n");
	free(redir->target);
	hd.fd_tmp = open("/tmp/minishell_fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("\U0001F984 ", 2);
	hd.line = get_next_line(STDIN_FILENO);
	hd.exp = 0;
	return (hd);
}

static int	ft_heredoc_next_line(t_heredoc *hd)
{
	char		*tmp;

	while (1)
	{
		tmp = hd->input;
		hd->input = ft_strjoin(hd->input, hd->line);
		if (tmp[0])
			free(tmp);
		free(hd->line);
		ft_putstr_fd("\U0001F984 ", 2);
		hd->line = get_next_line(STDIN_FILENO);
		if (!hd->line)
			return (1);
		if (ft_strcmp(hd->line, hd->word) == 0)
			break ;
	}
	return (0);
}

int	ft_heredoc_in(t_redir *redir, t_minishell shell)
{
	t_heredoc	hd;

	hd = ft_init_heredoc(redir);
	if (signal(SIGINT, &ft_sig_hd_handle) == SIG_ERR
		|| signal(SIGQUIT, &ft_sig_hd_handle) == SIG_ERR)
		return (hd.fd_tmp);
	if (!hd.line || ft_strcmp(hd.line, hd.word) == 0)
		return (ft_free_hd_var(hd, 1));
	if (ft_heredoc_next_line(&hd))
		return (ft_free_hd_var(hd, 2));
	if (redir->type == P_RT_HEREDOC_QUOTED)
		hd.exp = expand(hd.input, 0, &shell);
	else
		hd.exp = expand(hd.input, E_FORCE_VAR, &shell);
	if (hd.fd_tmp == -1)
		ft_hd_error();
	ft_putstr_fd(hd.exp->result, hd.fd_tmp);
	return (ft_free_hd_var(hd, 3));
}

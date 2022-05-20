/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:25:50 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 17:28:32 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <string.h>
#include <sys.h>

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
	g_out = 1;
}

int	ft_free_hd_var(t_heredoc hd, int c)
{
	if (c == 1)
	{
		if (hd.line)
			free(hd.line);
		free(hd.word);
	}
	if (c == 2)
	{
		free(hd.input);
		free(hd.word);
	}
	if (c == 3)
	{
		free(hd.line);
		free(hd.input);
		free(hd.exp->result);
		hd.exp->destroy(hd.exp);
		free(hd.word);
	}
	return (hd.fd_tmp);
}

void	ft_hd_error(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Cannot create tmp file\n", 2);
}

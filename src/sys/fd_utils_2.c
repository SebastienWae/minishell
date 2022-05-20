/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:25:50 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 13:30:36 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <string.h>

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

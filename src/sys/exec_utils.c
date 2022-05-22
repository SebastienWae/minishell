/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:18:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/22 19:32:33 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <minishell.h>
#include <sys.h>
#include <sys/wait.h>

void	ft_launch_proc(t_minishell shell, t_list *cmd, int fd_tab[2])
{
	ft_current_process(shell, cmd, fd_tab);
	exit(g_out);
}

void	set_exit_code(pid_t process)
{
	int	status;

	waitpid(process, &status, 0);
	g_out = WEXITSTATUS(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/21 19:30:31 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>
#include <sys.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_launch_cmd(char **cmd, t_minishell shell, t_parser *parsed)
{
	if (cmd[0] && ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, shell, parsed);
	else if (cmd[0] && ft_is_builtin_cmd(cmd[0]))
		shell.local_env = ft_execute_builtin_cmd(cmd, shell.local_env);
	else
		g_out = ft_sys_cmd_process(cmd, shell.local_env);
}

static int	ft_next_process(pid_t process, int fd_tab[2])
{
	int	status;

	waitpid(process, &status, WNOHANG);
	dup2(fd_tab[0], STDIN_FILENO);
	close(fd_tab[1]);
	close(fd_tab[0]);
	g_out = WEXITSTATUS(status);
	return (g_out);
}

static void	ft_current_process(t_minishell shell, t_list *cmd, int fd_tab[2])
{
	int	fd_in;
	int	fd_out;

	close(fd_tab[0]);
	fd_in = 0;
	fd_out = 1;
	if (cmd->next)
		dup2(fd_tab[1], STDOUT_FILENO);
	if (((t_cmd *)(cmd->content))->out)
		fd_out = ft_fd_manager((t_cmd *)(cmd->content), 2, shell).out;
	if (fd_in != -1 && ((t_cmd *)(cmd->content))->cmd)
	{
		if (ft_strcmp(((t_cmd *)(cmd->content))->cmd->values[0], "exit") != 0)
		{
			if (ft_is_builtin_cmd(((t_cmd *)(cmd->content))->cmd->values[0]))
				ft_execute_builtin_cmd(((t_cmd *)(cmd->content))->cmd->values,
					shell.local_env);
			else
				ft_execute_sys_cmd(((t_cmd *)(cmd->content))->cmd->values,
					shell.local_env);
		}
	}
	close(fd_tab[1]);
	close(fd_in);
	close(fd_out);
}

void	ft_launch_next_process(t_minishell shell, t_list *cmd, pid_t process,
		int fd_tab[2])
{
	if ((t_cmd *)cmd->next)
		g_out = ft_next_process(process, fd_tab);
	else
	{
		close(fd_tab[1]);
		close(fd_tab[0]);
	}
	if (((t_cmd *)(cmd->next)) && ((t_cmd *)(cmd->next->content))->in)
		dup2(shell.saved_stdin, STDIN_FILENO);
}

t_minishell	ft_pipe(t_minishell shell, t_list *cmd)
{
	int			fd_tab[2];
	t_fd_in_out	fd;
	pid_t		process;

	while (cmd)
	{
		if (pipe(fd_tab) == -1)
			return (ft_pipe_error(shell, 1));
		if (((t_cmd *)(cmd->content))->in)
			fd = ft_fd_manager((t_cmd *)(cmd->content), 1, shell);
		process = fork();
		if (process == -1)
			return (ft_pipe_error(shell, 2));
		if (process == 0)
		{
			ft_current_process(shell, cmd, fd_tab);
			exit(g_out);
		}
		else
			ft_launch_next_process(shell, cmd, process, fd_tab);
		if (fd.in != 0)
			close(fd.in);
		cmd = cmd->next;
	}
	return (shell);
}

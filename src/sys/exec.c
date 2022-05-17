/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/17 15:14:34 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>
#include <minishell.h>
#include <sys.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utils.h>

void	ft_launch_cmd(char **cmd, t_minishell shell, char **env)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, shell);
	else if (ft_is_builtin_cmd(cmd[0]))
		shell.local_env = ft_execute_builtin_cmd(cmd, shell.local_env);
	else
		g_out = ft_sys_cmd_process(cmd, shell.local_env, env);
}

static int	ft_next_process(pid_t process, int fd_tab[2])
{
	int	status;

	waitpid(process, &status, 0);
	close(fd_tab[1]);
	dup2(fd_tab[0], STDIN_FILENO);
	g_out = WEXITSTATUS(status);
	return (g_out);
}

static void	ft_current_process(t_minishell shell, t_list *cmd, char **env,
		int fd_tab[2])
{
	t_fd_in_out	fd;

	fd.in = 0;
	close(fd_tab[0]);
	if (((t_cmd *)(cmd->content))->in)
		fd = ft_fd_manager((t_cmd *)(cmd->content), 1, shell);
	if (cmd->next)
		dup2(fd_tab[1], STDOUT_FILENO);
	if (((t_cmd *)(cmd->content))->out)
		fd = ft_fd_manager((t_cmd *)(cmd->content), 2, shell);
	if (fd.in != -1)
		ft_launch_cmd(((t_cmd *)(cmd->content))->cmd->values, shell, env);
}

t_minishell	ft_pipe_error(t_minishell shell, int choice)
{
	if (choice == 1)
		ft_putstr_fd("Pipe initialization failed\n", 2);
	if (choice == 2)
		ft_putstr_fd("Pipe process failed\n", 2);
	return (shell);
}

t_minishell	ft_pipe(t_minishell shell, t_list *cmd, char **env)
{
	int		fd_tab[2];
	pid_t	process;

	while (cmd != 0)
	{
		if (pipe(fd_tab) == -1)
			return (ft_pipe_error(shell, 1));
		process = fork();
		if (process == -1)
			return (ft_pipe_error(shell, 2));
		if (process == 0)
		{
			ft_current_process(shell, cmd, env, fd_tab);
			exit(g_out);
		}
		else
		{
			g_out = ft_next_process(process, fd_tab);
			if (((t_cmd *)(cmd->next)) && ((t_cmd *)(cmd->next->content))->in)
				dup2(shell.saved_stdin, STDIN_FILENO);
		}
		cmd = cmd->next;
	}
	return (shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/19 19:19:49 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <functions.h>
#include <minishell.h>
#include <sys.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utils.h>

void	ft_launch_cmd(char **cmd, t_minishell shell, char **env)
{
	if (cmd[0] && ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, shell);
	else if (cmd[0] && ft_is_builtin_cmd(cmd[0]))
		shell.local_env = ft_execute_builtin_cmd(cmd, shell.local_env);
	else
		g_out = ft_sys_cmd_process(cmd, shell.local_env, env);
}

#include <signal.h>
#include <stdio.h>
static int	ft_next_process(pid_t process, int fd_tab[2])
{
	int	status;

	waitpid(process, &status, WNOHANG);
	dup2(fd_tab[0], STDIN_FILENO);
	close(fd_tab[1]);
	close(fd_tab[0]);
	//kill (process, SIGQUIT);
	/*
	if (WIFEXITED(status))
		printf("exit");
	if (WIFSIGNALED(status))
		printf("signal");
	if (WIFSTOPPED(status)){
		printf("stop");
		
	}*/
	g_out = WEXITSTATUS(status);
	return (g_out);
}

static void	ft_current_process(t_minishell shell, t_list *cmd, char **env,
		int fd_tab[2])
{
	int	fd_in;
	int	fd_out;

	close(fd_tab[0]);
	(void)env;
	fd_in = 0;
	fd_out = 1;
	if (((t_cmd *)(cmd->content))->in)
		fd_in = ft_fd_manager((t_cmd *)(cmd->content), 1, shell).in;
	if (cmd->next)
		dup2(fd_tab[1], STDOUT_FILENO);
	if (((t_cmd *)(cmd->content))->out)
	{
		fd_out = ft_fd_manager((t_cmd *)(cmd->content), 2, shell).out;
		/*close(fd_tab[0]);
		if (fd_out == 1)
			close (fd_out);*/
	}
	if (fd_in != -1 && ((t_cmd *)(cmd->content))->cmd)
	{
		if (ft_is_builtin_cmd(((t_cmd *)(cmd->content))->cmd->values[0]))
			ft_execute_builtin_cmd(((t_cmd *)(cmd->content))->cmd->values,
									shell.local_env);
		else
			ft_execute_sys_cmd(((t_cmd *)(cmd->content))->cmd->values,
								shell.local_env);
		//ajout exit : ne rien faire
	}
	close(fd_tab[1]);
	close(fd_in);
	close(fd_out);
}

t_minishell	ft_pipe_error(t_minishell shell, int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("Pipe initialization failed\n", 2);
	}
	if (choice == 2)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("Fork failed\n", 2);
	}
	return (shell);
}

t_minishell	ft_pipe(t_minishell shell, t_list *cmd, char **env)
{
	int		fd_tab[2];
	pid_t	process;

	//pid_t	prev_process;
	//int		prev_fd_tab[2];
	while (cmd)
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
			if ((t_cmd *)cmd->next)
				g_out = ft_next_process(process, fd_tab);
			else
			{
				//waitpid (prev_process, 0, WNOHANG);
				/*while (close (0) != -1);
				while (close (1) != -1);
				close (1);
				close (prev_fd_tab[1]);
				close (prev_fd_tab[0]);*/
				//close(shell.saved_stdin);
				//close(shell.saved_stdout);
				close(fd_tab[1]);
				close(fd_tab[0]);
				//kill(prev_process, SIGTERM);
			}
			if (((t_cmd *)(cmd->next)) && ((t_cmd *)(cmd->next->content))->in)
				dup2(shell.saved_stdin, STDIN_FILENO);
		}
		cmd = cmd->next;
		//prev_fd_tab[0] = fd_tab[0];
		//prev_fd_tab[1] = fd_tab[1];
		//prev_process = process;
	}
	return (shell);
}

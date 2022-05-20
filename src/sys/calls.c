/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:44 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 13:59:26 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#if __linux__
# include <sys/wait.h>
#endif

char	*ft_search_path(t_list *local_env)
{
	char	*path;

	path = NULL;
	while (local_env && ft_strncmp("PATH=", (char *)local_env->content, 5))
		local_env = local_env->next;
	if (local_env == NULL)
		return (NULL);
	path = ft_substr((char *)local_env->content, 5,
			ft_strlen((char *)local_env->content) - 5);
	return (path);
}

char	*ft_build_cmd(char **path, char *cmd)
{
	char	*str;
	char	*cmd_out;

	if (cmd && cmd[0] == '/')
		if (access(cmd, 0) == 0)
			return (cmd);
	if (cmd && cmd[0] == '.')
	{
		if (access(cmd, 0) == 0)
			return (cmd);
		else
			return (0);
	}
	if (path == NULL)
		return (0);
	while (*path)
	{
		str = ft_strjoin(*path, "/");
		cmd_out = ft_strjoin(str, cmd);
		free(str);
		if (access(cmd_out, 0) == 0)
			return (cmd_out);
		free(cmd_out);
		path++;
	}
	return (0);
}

int	*ft_execute_sys_cmd(char **cmd, t_list *local_env)
{
	char	*main_cmd;
	char	**path_list;
	char	*path_env_var;
	int		i;

	path_env_var = ft_search_path(local_env);
	path_list = ft_split(path_env_var, ':');
	main_cmd = ft_build_cmd(path_list, cmd[0]);
	i = 0;
	while (path_list && path_list[i])
	{
		free(path_list[i]);
		i ++;
	}
	free(path_list);
	free(path_env_var);
	if (main_cmd == NULL || cmd[0][0] == 0)
	{			
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[0], 2);
		if (cmd[0][0] == '.' || cmd[0][0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		if (main_cmd)
			free (main_cmd);
		exit(127);
	}
	if (execve(main_cmd, cmd, 0) == -1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		free(main_cmd);
		exit(1);
	}
	free(main_cmd);
	return (0);
}

void	ft_sig_process_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
		return ;
}

int	ft_sys_cmd_process(char **cmd, t_list *local_env)
{
	pid_t	process;
	int		status;

	process = fork();
	if (signal(SIGINT, &ft_sig_process_handle) == SIG_ERR
		|| signal(SIGQUIT, &ft_sig_process_handle) == SIG_ERR)
	{
		kill (process, 0);
		return (g_out);
	}
	if (process == 0)
		ft_execute_sys_cmd(cmd, local_env);
	else
	{
		waitpid(process, &status, 0);
		g_out = WEXITSTATUS(status);
	}	
	return (g_out);
}

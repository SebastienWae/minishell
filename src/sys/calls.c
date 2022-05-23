/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:14:43 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 15:26:44 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <string.h>
#include <signal.h>
#include <sys.h>
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

	path_env_var = ft_search_path(local_env);
	path_list = ft_split(path_env_var, ':');
	main_cmd = ft_build_cmd(path_list, cmd[0]);
	ft_free_path_list(path_list);
	free(path_list);
	free(path_env_var);
	if (main_cmd == NULL || cmd[0][0] == 0)
		ft_sys_cmd_error(cmd, main_cmd);
	if (main_cmd && execve(main_cmd, cmd, 0) == -1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		free(main_cmd);
		exit(1);
	}
	else
		free(main_cmd);
	return (0);
}

static void	ft_sig_process_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
		return ;
}

void	ft_sys_cmd_process(char **cmd, t_list *local_env)
{
	pid_t	process;
	int		status;

	process = fork();
	if (signal(SIGINT, &ft_sig_process_handle) == SIG_ERR
		|| signal(SIGQUIT, &ft_sig_process_handle) == SIG_ERR)
	{
		kill (process, 0);
		return ;
	}
	if (process == 0)
		ft_execute_sys_cmd(cmd, local_env);
	else
	{
		waitpid(process, &status, 0);
		g_out = WEXITSTATUS(status);
	}	
}

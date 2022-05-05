/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:44 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/28 14:44:47 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

char	*ft_search_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env ++;
	return (*env + 5);
}

char	*ft_build_cmd(char **path, char *cmd)
{
	char	*str;
	char	*cmd_out;

	if (cmd[0] == '/')
		if (access(cmd, 0) == 0)
			return (cmd);
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

int	ft_execute_sys_cmd(char **cmd, char **env)
{
	char	*main_cmd;

	main_cmd = ft_build_cmd(ft_better_split(ft_search_path(env), ':'), cmd[0]);
	if (main_cmd == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}	
	if (execve(main_cmd, cmd, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}	
	free(main_cmd);
	ft_free_char_tab(cmd);
	return (0);
}

void	ft_fake_pipex_to_test(char **env)
{
	char	**buffer;

	buffer = malloc(sizeof(char *) * 5);
	buffer[0] = "./pipex";
	buffer[1] = "f1";
	buffer[2] = "tr 'z' 'y'";
	buffer[3] = "tr 'y' '@'";
	buffer[4] = "f2";
	main_pipex(5, buffer, env);
}

void	ft_sys_cmd_process (char **parsed_str, char *str, char **env)
{
	pid_t	process;

	process = fork ();
	if (process == 0)
	{
		if (ft_strcmp(str, "pipe") == 0) // changer par si IN_PIPE
			ft_fake_pipex_to_test(env); // j'ai peur pour la transition
		else
			ft_execute_sys_cmd(parsed_str, env);
	}
	else
		waitpid(process, NULL, 0);
	kill(process, SIGQUIT); // a l'air de corriger le bug avec exit apres pipe
}

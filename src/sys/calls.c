/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:44 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 15:30:05 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <minishell.h>

//TODO: remove
char	**ft_better_split(char *s, char c);

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

int	*ft_execute_sys_cmd(char **cmd, char **env)
{
	char	*main_cmd;

	main_cmd = ft_build_cmd(ft_better_split(ft_search_path(env), ':'), cmd[0]);
	if (main_cmd == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}	
	if (execve(main_cmd, cmd, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(main_cmd);
		//ft_free_char_tab(cmd);
		exit (1);
	}	
	free(main_cmd);
	//ft_free_char_tab(cmd);
	return (0);
}

int	ft_sys_cmd_process(char **parsed_str, char *str, char **env)
{
	pid_t	process;
	int		status;

	(void)str;
	process = fork();
	if (process == 0)
		ft_execute_sys_cmd(parsed_str, env);
	else
	{
		waitpid(process, &status, 0);
		g_out = WEXITSTATUS(status);
	}
	return (g_out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:44 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/12 17:44:31 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <minishell.h>

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

	if (cmd[0] == '/')
		if (access(cmd, 0) == 0)
			return (cmd);
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

	main_cmd = ft_build_cmd(ft_split(ft_search_path(local_env), ':'), cmd[0]);
	if (main_cmd == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}	
	if (execve(main_cmd, cmd, 0) == -1)
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

int	ft_sys_cmd_process(char **parsed_str, char *str, t_list *local_env)
{
	pid_t	process;
	int		status;

	(void)str;
	process = fork();
	if (process == 0)
		ft_execute_sys_cmd(parsed_str, local_env);
	else
	{
		waitpid(process, &status, 0);
		g_out = WEXITSTATUS(status);
	}
	return (g_out);
}

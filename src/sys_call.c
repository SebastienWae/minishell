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

#include "minishell.h"
#include <errno.h>
#include <string.h>

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

//ajouter fichier entree fichier sortie
int	ft_execute_sys_cmd(char **cmd, char **env)
{
	char	*main_cmd;

	main_cmd = ft_build_cmd(ft_better_split(ft_search_path(env), ':'), cmd[0]);
	if (main_cmd == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	//dup2(cmd.input_file, STDIN_FILENO); si entree != stdin
	//dup2(fd_tab[1], STDOUT_FILENO); si sortie != stdout		
	if (execve(main_cmd, cmd, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}	
	free(main_cmd);
	ft_free_char_tab(cmd);
	return (0);
}

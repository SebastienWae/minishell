/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:38:27 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 16:46:56 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_path_list(char	**path_list)
{
	int	i;

	i = 0;
	while (path_list && path_list[i])
	{
		free(path_list[i]);
		i ++;
	}
}

void	ft_sys_cmd_error(char **cmd, char *main_cmd)
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

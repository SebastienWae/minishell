/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/05 11:56:41 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_pipex	ft_init_fd(char **argv, char **env)
{
	t_pipex	cmd;

	cmd.path = ft_better_split(ft_search_path(env), ':');
	cmd.input_file = open(argv[1], O_RDONLY);
	if (cmd.input_file == -1)
		ft_putstr_fd(strerror(errno), 2);
	cmd.output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd.output_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	return (cmd);
}

void	ft_process_1(char **argv, char **env, int fd_tab[2], t_pipex cmd)
{
	cmd.arg1 = ft_better_split(argv[2], ' ');
	cmd.main1 = ft_build_cmd(cmd.path, cmd.arg1[0]);
	if (cmd.main1 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_free_all(cmd, 1);
		exit(127);
	}
	if (cmd.input_file != -1)
	{
		dup2(cmd.input_file, STDIN_FILENO);
		dup2(fd_tab[1], STDOUT_FILENO);
		close(fd_tab[0]);
		if (execve(cmd.main1, cmd.arg1, env) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_free_all(cmd, 1);
			exit (1);
		}
		close(cmd.input_file);
	}		
	free(cmd.main1);
	ft_free_char_tab(cmd.arg1);
}

void	ft_process_2(char **argv, char **env, int fd_tab[2], t_pipex cmd)
{
	cmd.arg2 = ft_better_split(argv[3], ' ');
	cmd.main2 = ft_build_cmd(cmd.path, cmd.arg2[0]);
	if (cmd.main2 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_free_all(cmd, 2);
		exit(127);
	}
	dup2(fd_tab[0], STDIN_FILENO);
	close(fd_tab[1]);
	dup2(cmd.output_file, STDOUT_FILENO);
	if (execve(cmd.main2, cmd.arg2, env) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_free_all(cmd, 2);
		exit (1);
	}
	close(cmd.output_file);
}

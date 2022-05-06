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
#include <init_functions.h>

t_pipex	ft_init_fd(char **argv, char **env, t_fd_in_out fd)
{
	t_pipex	cmd;

	(void) argv;
	cmd.path = ft_better_split(ft_search_path(env), ':');
	//cmd.input_file = dup(fd.in);
	cmd.input_file = open("file_test_pipe", O_RDONLY);
	if (cmd.input_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
	}
	cmd.output_file = dup(fd.out);
	if (cmd.output_file == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
	return (cmd);
}

void	ft_process_1(char **argv, char **env, int fd_tab[2], t_pipex cmd)
{
	cmd.arg1 = ft_better_split(argv[0], ' ');
	cmd.main1 = ft_build_cmd(cmd.path, cmd.arg1[0]);
	if (cmd.main1 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_free_all(cmd, 1);
		exit (127);
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
	cmd.arg2 = ft_better_split(argv[1], ' ');
	cmd.main2 = ft_build_cmd(cmd.path, cmd.arg2[0]);
	if (cmd.main2 == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_free_all(cmd, 2);
		exit (127);
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

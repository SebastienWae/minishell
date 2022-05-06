/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:17 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/18 12:24:11 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/wait.h>


void	ft_launch_cmd_full(int fd_tab[2], char **argv, char **env, t_pipex cmd)
{
	pid_t	process;

	process = fork();
	if (process == -1)
		ft_error_exit(cmd);
	if (process == 0)
		ft_process_1(argv, env, fd_tab, cmd);
	else
	{	
		waitpid(process, NULL, WNOHANG);
		ft_process_2(argv, env, fd_tab, cmd);			
	}
	ft_free_all(cmd, 4);
}

int	main_pipex(char **all_cmds, char **env, t_fd_in_out fd)
{
	
	int		fd_tab[2];
	t_pipex	cmd;

	//ft_nb_arg_error(argc);
	if (pipe(fd_tab) == -1)
		ft_error_exit_arg();
	cmd = ft_init_fd(all_cmds, env, fd);
	if (cmd.input_file != -1)
		ft_launch_cmd_full(fd_tab, all_cmds, env, cmd);
	else 
	{
		ft_process_2(all_cmds, env, fd_tab, cmd);
		ft_free_all(cmd, 2);
	}
	return (0);
}

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

#include "minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
int	main_pipex(int argc, char **argv, char **env)
{
	pid_t	process;
	int		p;
	int		fd_tab[2];
	t_pipex	cmd;

	ft_nb_arg_error(argc);
	p = pipe(fd_tab);
	if (p == -1)
		ft_error_exit_arg();
	cmd = ft_init_fd(argv, env);
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
	return (0);
}

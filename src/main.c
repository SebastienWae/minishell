/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:02 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/29 17:41:04 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <sig_handler.h>
#include <built_in_functions.h>
#include <init_functions.h>
#include <close_functions.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

t_minishell	ft_launch_cmd(char *str, t_minishell shell, char **env)
{
	char	**parsed_str;
	add_history(str);				
	parsed_str = ft_better_split(str, ' '); // a remplacer 
	if (ft_strcmp(parsed_str[0], "exit") == 0)
		ft_exit(parsed_str);
	else if (ft_is_builtin_cmd(parsed_str[0]))
		shell.local_env = ft_execute_builtin_cmd(parsed_str, shell.local_env);
	else
		ft_sys_cmd_process(parsed_str, str, env);
	free (parsed_str);	
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		shell;
	char			*str;
	t_fd_in_out		fd;

	shell = ft_init_all(argc, argv, env);
	while (1)
	{
		str = readline("Minishell>");			
		if (ft_ctrl_d_handler(str))
		{
			fd = ft_init_fd_minishell();
			if (str[0] != 0)
				shell = ft_launch_cmd(str, shell, env);
			ft_close_fd(shell, fd.in, fd.out);
		}
		free (str);	
	}
	ft_close_saved_fd(shell);
	return (0);
}

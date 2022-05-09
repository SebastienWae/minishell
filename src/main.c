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
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
# include <signal.h>

void   ft_heredoc_in(char *cmd, t_minishell shell, char **env);

t_minishell	ft_launch_cmd(char *str, t_minishell shell, char **env)
{
	char	**parsed_str;


	parsed_str = ft_better_split(str, ' '); // a remplacer ou enlever selon le retour de seb
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

	shell = ft_init_all(argc, argv, env); // init env, config, sig, save default stdin and out 
	while (1)
	{
		str = readline("Minishell>");
		if (ft_ctrl_d_handler(str))
		{
			add_history(str);			
			fd = ft_init_fd_minishell(); //=> met a 0 et 1 au depart		
/*
			if (str[0] == '@') //test pour heredoc
				ft_heredoc_in("cat -e", shell, env);

			else */
			if (str[0] != 0)
			{
			
				if (ft_strcmp(str, "pipe") == 0) //sort le resultat de la derniere sur stdout mais pas pipe
				{
					char	**buffer;
					buffer = malloc(sizeof(char *) * 4);
					buffer[0] = "cat f1";	
					buffer[1] = "grep blou";
					buffer[2] = "wc";
					buffer[3] = 0;
					int	i = 0;
					int fd_tab[2];
					pid_t process;				
													
					
					while(buffer[i] != 0 )
					{	
									
						pipe(fd_tab);							
						process = fork();											
						if (process == 0)
						{				
							close(fd_tab[0]);
							if(buffer[i + 1] != NULL)									
								dup2(fd_tab[1], STDOUT_FILENO);															
							shell = ft_launch_cmd(buffer[i], shell, env);							
							exit(0);
						}
						else
						{
							waitpid(process, NULL, 0);	
							close(fd_tab[1]);						
							dup2 (fd_tab[0], STDIN_FILENO);													
							i ++;								
						}													
					}					
				}
				else // une seule commande
					shell = ft_launch_cmd(str, shell, env);		
			}
			ft_close_fd(shell, fd.in, fd.out); //restaure les stdin et out par defaut pour le rendre a readline
		}
		free (str);	
	}
	ft_close_saved_fd(shell);
	return (0);
}

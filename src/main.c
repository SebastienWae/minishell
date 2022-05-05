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

void	ft_fake_pipex_to_test(char **env)
{
	char	**buffer;

	buffer = malloc(sizeof(char *) * 5);
	buffer[0] = "./pipex";
	buffer[1] = "f1";
	buffer[2] = "tr 'z' 'y'";
	buffer[3] = "tr 'y' '@'";
	buffer[4] = "f2";
	main_pipex(5, buffer, env);
}
/*
typedef struct s_minishell {
	t_list			*local_env;
	struct termios	config;
	int 			saved_stdin;
	int 			saved_stdout
} t_minishell;
*/
int	main(int argc, char **argv, char **env)
{
	t_minishell		shell;
	char			*str;
	char			**parsed_str;
	pid_t			process;

	shell = ft_init_all(argc, argv, env);
	while (1)
	{
		str = readline("Minishell>");
		//mettre ici le splitteur de commande
		//remplacer fd_in et fd_out par les fichiers precises sauf si pipe
		//int fd_out = open("f2", O_RDWR | O_CREAT | O_TRUNC, 0777);
		//int fd_in = open("f1", O_RDONLY);
		//dup2(fd_out, STDOUT_FILENO);	
		//dup2(fd_in, STDIN_FILENO);		
		if (ft_ctrl_d_handler(str))	//exit si str null = si ctrl d
			if (str[0] != 0)
			{
				add_history(str);				
				parsed_str = ft_better_split(str, ' '); // a remplacer 
				if (ft_strcmp(parsed_str[0], "exit") == 0)
					ft_exit(parsed_str);
				else if (ft_is_builtin_cmd(parsed_str[0]))
					shell.local_env = ft_execute_builtin_cmd(parsed_str, shell.local_env);
				else
				{
					process = fork ();
					if (process == 0)
					{
						if (ft_strcmp(str, "pipe") == 0) // changer par si IN_PIPE
							ft_fake_pipex_to_test(env);
						else
							ft_execute_sys_cmd(parsed_str, env);
					}
					else
						waitpid(process, NULL, 0);
				}
				free (parsed_str);
				free (str);			
			}	
			//dup2 (saved_stdout, 1);
			//dup2 (saved_stdin, 0);
			//close(fd_out);			
			//close(fd_in);						
	}
	close(shell.saved_stdout);
	close(shell.saved_stdin);
	return (0);
}

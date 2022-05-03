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
#include <unistd.h>
#include <termios.h>
#include <errno.h>

int	g_out = 0;
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

int	main(int argc, char **argv, char **env)
{
	char			*str;
	char			**parsed_str;
	pid_t			process;
	static t_list	*local_env;
	struct termios	config;

	(void) argv;
	tcgetattr(STDIN_FILENO, &config);
	config.c_lflag &= ~(ECHOCTL);
	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	local_env = NULL;
	ft_check_arg_error(argc);
	local_env = ft_init_env(env);
	ft_sig();
	while (1)
	{
		str = readline("Minishell>");
		if (ft_ctrl_d_handler(str))	//exit si str null = si ctrl d
			if (str[0] != 0)
			{
				add_history(str);
				parsed_str = ft_better_split(str, ' ');
				if (ft_strcmp(parsed_str[0], "exit") == 0)
					ft_exit(parsed_str);
				else if (ft_is_builtin_cmd(parsed_str[0]))
					local_env = ft_execute_builtin_cmd(parsed_str, local_env);
				else
				{
					process = fork ();
					if (process == 0)
					{
						if (ft_strcmp(str, "pipe") == 0)
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
	}
	return (0);
}

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

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

t_list	*g_local_env = NULL;

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

int ft_exit(char **str)
{
	int	i;
	
	i = 0;
	if (str[1] == 0)
	{
		printf("exit\n");
		exit (0);
	}
	else
	{
		while (str[1][i] != 0)
		{
			if (!ft_isdigit(str[1][i]))
			{
				printf("exit: %s: numeric argument required\n", str[1]);
				exit(255);
			}
			i ++;
		}	
	}
	if (str[2] != 0)
	{
		printf("exit\nexit: too many arguments\n");
		return (0);
	}
	exit (ft_atoi(str[1]));
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	**parsed_str;
	pid_t	process;

	(void) argv;
	ft_check_arg_error(argc);
	while (1)
	{
		str = NULL;
		parsed_str = NULL;
		str = readline("Unicorn@Zombie_apocalypse>");
		if (str[0] != 0)	
		{
			parsed_str = ft_better_split(str, ' ');
			if (ft_strcmp(parsed_str[0], "exit") == 0)
				ft_exit(parsed_str);
			else if (ft_is_builtin_cmd(parsed_str[0]))
				g_local_env = ft_execute_builtin_cmd(parsed_str, g_local_env);
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
	return(0);
}

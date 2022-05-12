/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:02 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/12 16:13:53 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <utils.h>
#include <sys.h>

int	g_out;

static void	args_check_error(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Minishell does not take arguments\n", 2);
		exit(0);
	}
}

static struct termios	init_termios(void)
{
	struct termios	config;

	tcgetattr(STDIN_FILENO, &config);
	config.c_lflag &= ~(ECHOCTL);
	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	return (config);
}

static t_list	*init_env(char **env)
{
	t_list	*local_env;
	int		i;

	local_env = NULL;
	i = -1;
	while (env[++i])
	{
		ft_lstadd_back(&local_env,
			ft_lstnew(ft_strncpy(env[i], 0, ft_strlen(env[i]))));
	}
	return (local_env);
}

static t_minishell	init_all(int argc, char **env)
{
	t_minishell		shell;

	g_out = 0;
	args_check_error(argc);
	shell.config = init_termios();
	shell.local_env = init_env(env);
	ft_sig();
	shell.saved_stdin = dup(STDIN_FILENO);
	shell.saved_stdout = dup(STDOUT_FILENO);
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		shell;
	char			*str;
	t_fd_in_out		fd;

	(void)argv;
	shell = init_all(argc, env); // init env, config, sig, save default stdin and out 
	while (1)
	{
		str = readline("Minishell>");
		if (ft_ctrl_d_handler(str))
		{
			add_history(str);
			//ajouter ici appel fonction seb		
			fd = ft_init_fd_minishell(); // a modifier pour mettre les fd de la cmd
			if (str[0] == '@') //test provisoire heredoc
				ft_heredoc_in("cat -e", shell, env);
			else
				if (str[0] != 0)
				{			
					if (ft_strcmp(str, "pipe") == 0) // test provisoire pipe
						ft_pipe(shell); // remplacer avec appel sur liste de cmd
					else // une seule commande
						ft_launch_cmd(str, shell);	// remplacer par commande
				}
			ft_close_fd(shell, fd.in, fd.out); //restaure les stdin et out par defaut pour le rendre a readline
		}
		free(str);
	}
	ft_close_saved_fd(shell);
	ft_lstclear(&shell.local_env, free);
	return (0);
}

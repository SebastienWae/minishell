/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:59:05 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/04 15:59:08 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sig_handler.h>
#include <init.h>

struct termios	ft_init_config(void)
{
	struct termios	config;

	tcgetattr(STDIN_FILENO, &config);
	config.c_lflag &= ~(ECHOCTL);
	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	return (config);
}

//voir si variables a changer ds l'env
t_list	*ft_init_env(char **env)
{
	t_list	*local_env;
	int		i;

	local_env = NULL;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("SHELL", env[i], 5))
			ft_lstadd_back(&local_env, ft_lstnew(ft_strncpy\
			("SHELL=Minishell", 0, 15)));
		else
			ft_lstadd_back(&local_env, ft_lstnew(ft_strncpy\
			(env[i], 0, ft_strlen(env[i]))));
	}
	return (local_env);
}

t_minishell	ft_init_all(int argc, char **argv, char **env)
{
	t_minishell		shell;

	(void) argv;
	g_out = 0;
	ft_check_arg_error(argc);
	shell.config = ft_init_config();	
	shell.local_env = ft_init_env(env);
	ft_sig();
	shell.saved_stdin = dup(STDIN_FILENO);
	shell.saved_stdout = dup(STDOUT_FILENO);
	return (shell);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:02 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 14:07:42 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <errno.h>
#include <stdlib.h>
#include <sys.h>
#include <sys/wait.h>
#include <termios.h>
#include <tokenizer.h>
#include <unistd.h>
#include <utils.h>

#include <debug.h>

int						g_out;

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
	t_minishell	shell;

	g_out = 0;
	args_check_error(argc);
	shell.config = init_termios();
	shell.local_env = init_env(env);	
	shell.saved_stdin = dup(STDIN_FILENO);
	shell.saved_stdout = dup(STDOUT_FILENO);
	return (shell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;
	char		*str;
	t_fd_in_out	fd;
	t_parser	*parsed;
	t_tokenizer	*token;
	t_list		*cmd;

	(void)argv;
	shell = init_all(argc, env);
	while (1)
	{		
		ft_sig();
		while (wait(NULL) != -1 || errno != ECHILD);
		str = readline("Minishell> ");
		if (ft_ctrl_d_handler(str, shell))
		{
			if (str[0] != 0)
			{
				add_history(str);
				token = tokenize(str);
				if (!token)
				{
					ft_putstr_fd("Memory allocation failed. Aborting", 2);
					free(str);
					exit (1);
				}
				if (token->state == T_S_ERROR)
				{
					token->destroy(token);
					free(str);
					g_out = 2;
					continue ;
				}
				parsed = parse(token, &shell);
				if (!parsed)
				{
					ft_putstr_fd("Memory allocation failed. Aborting", 2);
					free(str);
					exit (1);
				}
				if (parsed->state == P_S_ERROR)
				{
					token->destroy(token);
					parsed->destroy(parsed);
					free(str);
					g_out = 2;
					continue ;
				}
				cmd = parsed->cmds;
				if (cmd && ((t_cmd *)(cmd->content))->cmd && ((t_cmd *)(cmd->content))->cmd->values)
				{
					if (((t_cmd *)(cmd->content))->piped == 1)
						ft_pipe(shell, cmd);
					else
					{
						while (cmd)
						{
							fd = ft_fd_manager((t_cmd *)(cmd->content), 0, shell);
							if (fd.in != -1 && fd.out != -1)
								ft_launch_cmd(((t_cmd *)(cmd->content))->cmd->values, shell, token, parsed);
							if (fd.in != 0)
								close(fd.in);
							if (fd.out != 1)
								close(fd.out);
							ft_reset_fd(shell);
							cmd = cmd->next;
						}
					}
				}
				else if (cmd && (((t_cmd *)(cmd->content))->in
					|| ((t_cmd *)(cmd->content))->out))
					ft_fd_manager((t_cmd *)(cmd->content), 0, shell);
				ft_reset_fd(shell);
				token->destroy(token);
				parsed->destroy(parsed);
			}
		}
		else
			free(str);
	}
	ft_close_saved_fd(shell);
	ft_lstclear(&shell.local_env, free);
	return (0);
}

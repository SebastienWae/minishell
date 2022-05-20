/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 14:29:18 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_exit_no_arg(char **str, t_minishell shell, t_tokenizer *token, t_parser *parsed)
{
	if (str[1] == 0)
	{
		printf("exit\n");
		ft_lstclear(&shell.local_env, free);
		token->destroy(token);
		parsed->destroy(parsed);
		exit(0);
	}
	return (0);
}

int	ft_exit(char **str, t_minishell shell, t_tokenizer *token, t_parser *parsed)
{
	int	i;

	i = -1;
	ft_exit_no_arg(str, shell, token, parsed);
	while (str[1][++i] != 0)
	{
		if (!ft_isdigit(str[1][i]))
		{
			printf("%s: exit: %s: numeric argument required\n",
				SHELL_NAME, str[1]);
			ft_lstclear(&shell.local_env, free);
			token->destroy(token);
			parsed->destroy(parsed);
			free(str);
			exit(255);
		}
	}
	if (str[2] != 0)
	{
		printf("exit\n%s: exit: too many arguments\n", SHELL_NAME);
		g_out = 1;
		return (1);
	}
	i = ft_atoi(str[1]);
	free(str);
	token->destroy(token);
	parsed->destroy(parsed);
	ft_lstclear(&shell.local_env, free);
	exit(i);
}

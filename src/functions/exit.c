/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 17:18:54 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_exit_no_arg(char **str, t_minishell shell, t_parser *parsed)
{
	if (str[1] == 0)
	{
		printf("exit\n");
		ft_lstclear(&shell.local_env, free);
		parsed->destroy(parsed);
		exit(0);
	}
	return (0);
}

static int	ft_exit_not_numeric_arg(char **str, t_minishell shell,
			t_parser *parsed)
{
	printf("%s: exit: %s: numeric argument required\n",
		SHELL_NAME, str[1]);
	ft_lstclear(&shell.local_env, free);
	parsed->destroy(parsed);
	exit(255);
}

int	ft_exit(char **str, t_minishell shell, t_parser *parsed)
{
	int	i;

	i = -1;
	ft_exit_no_arg(str, shell, parsed);
	while (str[1][++i] != 0)
		if (!ft_isdigit(str[1][i]))
			ft_exit_not_numeric_arg(str, shell, parsed);
	if (str[2] != 0)
	{
		printf("exit\n%s: exit: too many arguments\n", SHELL_NAME);
		g_out = 1;
		return (1);
	}
	i = ft_atoi(str[1]);
	parsed->destroy(parsed);
	ft_lstclear(&shell.local_env, free);
	exit(i);
}

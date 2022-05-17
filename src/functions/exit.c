/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/17 13:39:49 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_exit_no_arg(char **str, t_minishell shell)
{
	if (str[1] == 0)
	{
		printf("exit\n");
		ft_lstclear(&shell.local_env, free);
		free(str);
		exit(0);
	}
	return (0);
}

int	ft_exit(char **str, t_minishell shell)
{
	int	i;

	i = 0;
	ft_exit_no_arg(str, shell);
	while (str[1][i] != 0)
	{
		if (!ft_isdigit(str[1][i]))
		{
			printf("exit: %s: numeric argument required\n", str[1]);
			ft_lstclear(&shell.local_env, free);
			free(str);
			exit(255);
		}
		i++;
	}
	if (str[2] != 0)
	{
		printf("exit\nexit: too many arguments\n");
		g_out = 1;
		return (1);
	}
	i = ft_atoi(str[1]);
	free(str);
	ft_lstclear(&shell.local_env, free);
	exit(i);
}

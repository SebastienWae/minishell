/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 14:24:42 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_exit(char **str, t_minishell shell)
{
	int	i;

	i = 0;
	if (str[1] == 0)
	{
		printf("exit\n");
		ft_lstclear(&shell.local_env, free);
		free(str);
		exit (0);
	}
	while (str[1][i] != 0)
	{
		if (!ft_isdigit(str[1][i]))
		{
			printf("exit: %s: numeric argument required\n", str[1]);
			ft_lstclear(&shell.local_env, free);
			free(str);
			exit(255);
		}
		i ++;
	}		
	if (str[2] != 0)
	{
		printf("exit\nexit: too many arguments\n");
		return (0);
	}
	free(str);
	ft_lstclear(&shell.local_env, free);
	exit(ft_atoi(str[1]));
}

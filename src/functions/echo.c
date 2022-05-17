/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:36 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 19:12:08 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <utils.h>

void	ft_echo(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] == 0)
	{
		printf("\n");
		g_out = 0;
		return ;
	}
	if (ft_strcmp(cmd[1], "-n") == 0)
		i = 1;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		printf("\n");
	g_out = 0;
}

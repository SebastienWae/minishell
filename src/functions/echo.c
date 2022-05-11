/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:36 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 15:46:30 by swaegene         ###   ########.fr       */
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
		if (!(ft_strcmp(cmd[1], "-n") != 0 && i == 1)
			&& (!(i == 2 && ft_strcmp(cmd[1], "-n") == 0)))
			printf(" ");
		if (!ft_strcmp(cmd[i], "$?"))
			printf("%d", g_out);
		else
			printf("%s", cmd[i]);
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		printf("\n");
	g_out = 0;
}

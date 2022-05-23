/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:36 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 16:06:11 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <utils.h>

static int	echo_remove_flags(char **cmd)
{
	int	i;
	int	ii;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			ii = 2;
			while (cmd[i][ii])
			{
				if (cmd[i][ii] == 'n')
					ii++;
				else if (cmd[i][ii] != '\0')
					return (i);
			}
			i ++;
		}		
		else
			return (i);
	}
	return (i);
}

void	ft_echo(char **cmd)
{
	int	i;
	int	n_flag;

	if (cmd[1] == 0)
	{
		printf("\n");
		g_out = 0;
		return ;
	}
	i = echo_remove_flags(cmd);
	n_flag = 0;
	if (i > 1)
		n_flag = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	g_out = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:48 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/21 07:54:24 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

void	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": pwd : Error - Permission denied / Failure\n", 2);
		g_out = 1;
	}
	else
	{
		printf("%s\n", current_dir);
		g_out = 0;
	}
	free (current_dir);
}

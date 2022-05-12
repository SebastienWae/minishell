/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:48 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 15:45:01 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

void	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		ft_putstr_fd("pwd : Error - Permission denied / Failure\n", 2);
		g_out = 1;
	}
	else
	{
		printf("%s\n", current_dir);
		g_out = 0;
	}
	free (current_dir);
}

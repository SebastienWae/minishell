/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:08:07 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 14:10:27 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <functions.h>
#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

static int	ft_cd_error(char *dir)
{
	if (chdir(dir) == -1)
	{
		g_out = 1;
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

void	ft_cd(char **cmd, t_list *local_env)
{
	char	*old_dir;

	g_out = 0;
	old_dir = ft_get_env_var_value(local_env, "PWD");
	if (cmd[1] == 0)
		chdir(getenv("HOME"));
	else if (ft_cd_error(cmd[1]))
		return ;
	while (local_env)
	{
		if (!ft_strncmp("PWD=", local_env->content, 4))
		{		
			free(local_env->content);
			if (!getcwd(NULL, 0))
				local_env->content = ft_strjoin("PWD=", "ERROR");
			else
				local_env->content = ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		if (!ft_strncmp("OLDPWD=", local_env->content, 7))
		{			
			free(local_env->content);
			local_env->content = ft_strjoin("OLDPWD=", old_dir);
		}
		local_env = local_env->next;
	}
}
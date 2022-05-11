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

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

void	ft_cd(char **cmd, t_list *local_env)
{
	char	*old_dir;
	char	*c;

	g_out = 0;
	old_dir = getcwd (NULL, 0);
	if (cmd[1] == 0)
		chdir(getenv("HOME"));
	else if (chdir(cmd[1]) == -1)
	{
		g_out = 1;
		ft_putstr_fd(strerror(errno), 2);
		printf("\n");
	}
	while (local_env)
	{
		c = local_env->content;
		if (!ft_strncmp("PWD", local_env->content, 3))
		{
			if (c[3] == '=')
			{
				free(local_env->content);
				local_env->content = ft_strjoin("PWD=", getcwd (NULL, 0));
			}
		}
		if (!ft_strncmp("OLDPWD", local_env->content, 6))
		{
			if (c[6] == '=')
			{
				free(local_env->content);
				local_env->content = ft_strjoin("OLDPWD=", old_dir);
			}
		}
		local_env = local_env->next;
	}
}

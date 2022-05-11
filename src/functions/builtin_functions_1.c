/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/28 14:44:32 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <built_in_functions.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

//ok
void	ft_pwd(char **cmd)
{
	char	*current_dir;

	(void) cmd;
	current_dir = getcwd (NULL, 0);
	printf("%s\n", current_dir);
	free (current_dir);	
	g_out = 0;
}

//ok
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

//change egalement PWD et OLDPWD dans env
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
			if (c[3] == '=')
			{
				free(local_env->content);
				local_env->content = ft_strjoin("PWD=", getcwd (NULL, 0));
			}
		if (!ft_strncmp("OLDPWD", local_env->content, 6))
			if (c[6] == '=')
			{
				free(local_env->content);
				local_env->content = ft_strjoin("OLDPWD=", old_dir);
			}
		local_env = local_env->next;
	}
}

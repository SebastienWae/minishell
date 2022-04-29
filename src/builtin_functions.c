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


#include "pipex.h"
#include "minishell.h"

#include <stdio.h>

int	ft_pwd(char **cmd)
{
	char    *current_dir;
    size_t  size_char;

	size_char = 100;
    current_dir = malloc(100);
	if (cmd[1] == 0)
	{
		printf("%s\n",getcwd(current_dir, size_char));
	}
	else 
	{
		printf("pwd : too many arguments\n");
		free (current_dir);
		return (1);
	}
	free (current_dir);
	return (0);
}

int	ft_echo(char **cmd)
{
	int	i;
	
	if (ft_strcmp(cmd[1], "-n") == 0)
		i = 1;
	else 
		i = 0;
	while(cmd[++i])
	{
		if (i != 1)
			printf(" ");
		printf("%s", cmd[i]);
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		printf("\n");
	return (0);
}

int	ft_cd(char **cmd)
{
	if (cmd[2] != 0)
	{
		printf("cd: string not in pwd: %s", cmd[1]);
		return (1);
	}
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int	ft_export(char **cmd,t_list **local_env)
{
	printf("Fonction export a faire\n");
	t_list *new;

	new = ft_lstnew(cmd[1]);//a changer
	ft_lstadd_back(local_env, new);		
	return (0);
}

int	ft_unset(char **cmd, t_list **local_env)
{
	(void) local_env;
	(void) cmd;
	printf("Fonction unset a faire\n");		
	return (0);
}
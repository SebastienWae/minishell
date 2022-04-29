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
#include <errno.h>
#include <string.h>

int	ft_pwd(char **cmd)
{
	char	*current_dir;
	size_t	size_char;

	size_char = 100;
	current_dir = malloc(100);
	if (cmd[1] == 0)
		printf("%s\n", getcwd (current_dir, size_char));
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

	if (cmd[1] == 0)
	{
		printf("\n");
		return (0);
	}
	if (ft_strcmp(cmd[1], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (cmd[++i])
	{
		if (i != 1)
			printf(" ");
		printf("%s", cmd[i]);
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		printf("\n");
	return (0);
}

//ajouter si cd seul => racine user
int	ft_cd(char **cmd)
{
	if (cmd[1] == 0)
		return (0);
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		printf("\n");
		return (1);
	}
	return (0);
}

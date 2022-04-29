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

t_list	*ft_export(char **cmd,t_list *g_local_env) // faire rempla si deja 
{	
	t_list	*new;
	char	*elem;
	int		i;

	i = 1;
	if (cmd[1] == 0)
		ft_print_env(g_local_env, 2);
	else if (cmd[1] != 0)
	{
		while (cmd[i] != NULL)
		{
			if (ft_check_char_export(cmd[i]) && ft_equal_is_in(cmd[i]))
			{
				elem = cmd[i];
				new = ft_lstnew(elem);
				ft_lstadd_back(&g_local_env, new);
			}
			else if (!ft_check_char_export(cmd[i]))
				printf("export: %s: not a valid identifier\n", cmd[i]);
			i ++;
		}
	}	
	return (g_local_env);
}

t_list	*ft_unset(char **cmd, t_list *g_local_env)
{
	int		i;
	t_list	*tmp;

	tmp = g_local_env;
	if (cmd[1] == 0)
		return (0);
	while (g_local_env)
	{
		i = 1;
		while (cmd[i] && g_local_env)
		{
			if (ft_strncmp(cmd[i], (char *)g_local_env->content, ft_strlen(cmd[i])) == 0)
			{
				g_local_env->content = 0;
				free(g_local_env->content);
				if (ft_lstsize(g_local_env) == 1)
					return (NULL);
				g_local_env = g_local_env->next;
				tmp = g_local_env;
			}
			i ++;
		}
		i = 1;
		while (cmd[i] != 0 && g_local_env->next && g_local_env)
		{				
			if (ft_strncmp(cmd[i], (char *)g_local_env->next->content, ft_strlen(cmd[i])) == 0)
			{
				g_local_env->next->content = 0;
				free(g_local_env->next->content);
				if (g_local_env->next->next)
					g_local_env->next=g_local_env->next->next;
				else
					g_local_env->next = NULL;
			}		
			i ++;
		}	
		g_local_env = g_local_env->next;
	}
	return (tmp);
}

int	ft_env(char **cmd, t_list *g_local_env)
{
	if (cmd[1] != 0)
		printf("****** Permission denied ? ******** -- a changer");
	ft_print_env(g_local_env, 1);
	return (0);
}

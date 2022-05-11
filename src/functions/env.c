/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:18 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 15:47:08 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <functions.h>

static int	ft_print_env(t_list *local_env, int choice)
{
	while (local_env)
	{
		if (choice != 1)
			printf("declare -x ");
		printf("%s\n", (char *)local_env->content);
		local_env = local_env->next;
	}
	return (0);
}

static int	ft_check_char_export(char *str)
{
	int	i;

	i = 1;
	if (!(str[0] == '_' || ft_isalpha(str[0])))
		return (0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i ++;
	}
	return (1);
}

t_list	*ft_export(char **cmd, t_list *local_env)
{	
	char	*elem;
	int		i;

	i = 0;
	g_out = 0;
	if (cmd[1] == 0)
		ft_print_env(local_env, 2);
	else
	{
		while (cmd[++i])
		{
			if (ft_check_char_export(cmd[i]) && ft_strrchr(cmd[i], '='))
			{
				elem = ft_strncpy(cmd[i], 0, ft_strlen(cmd[i]));
				if (ft_is_already_in_env(local_env, elem) == 0)
					ft_lstadd_back(&local_env, ft_lstnew(elem));
			}
			else if (!ft_check_char_export(cmd[i]))
			{
				printf("export: %s: not a valid identifier\n", cmd[i]);
				g_out = 1;
			}
		}
	}
	return (local_env);
}

t_list	*ft_unset(char **cmd, t_list *local_env)
{
	t_list	*tmp;
	int		i;
	int		nb_cmd;
	char	*c;

	g_out = 0;
	nb_cmd = 0;
	while (cmd[nb_cmd])
		nb_cmd ++;
	tmp = local_env;
	i = 1;
	if (cmd[1] == 0)
		return (local_env);
	while (local_env)
	{
		while (i < nb_cmd && local_env)
		{
			if (cmd[i] && !ft_check_char_export(cmd[i]))
			{		
				printf("unset: %s: not a valid identifier\n", cmd[i]);
				cmd[i] = NULL;
				g_out = 1;
				i ++;
			}
			c = (char *)local_env->content;
			if (cmd[i] && ft_strncmp(cmd[i], c, ft_strlen(cmd[i])) == 0
				&& c[ft_strlen(cmd[i])] == '=')
			{
				local_env->content = 0;
				free(local_env->content);
				if (ft_lstsize(local_env) == 1)
					return (NULL);
				local_env = local_env->next;
				tmp = local_env;
			}
			i ++;
		}
		local_env = ft_check_next(cmd, local_env, nb_cmd);
		local_env = local_env->next;
	}
	return (tmp);
}

void	ft_env(char **cmd, t_list *local_env)
{
	if (cmd[1] != 0)
	{
		printf("env: does not take arguments\n");
		g_out = 1;
		return ;
	}
	ft_print_env(local_env, 1);
	g_out = 0;
}

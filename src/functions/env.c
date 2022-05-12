/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:18 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 16:01:35 by jeulliot         ###   ########.fr       */
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

static int	ft_check_export(char *str)
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

	g_out = 0;
	if (cmd[1] == 0)
		ft_print_env(local_env, 2);
	else
	{
		while (*cmd)
		{
			if (ft_check_export(*cmd) && ft_strrchr(*cmd, '='))
			{
				elem = ft_strncpy(*cmd, 0, ft_strlen(*cmd));
				if (ft_is_already_in_env(local_env, elem) == 0)
					ft_lstadd_back(&local_env, ft_lstnew(elem));
			}
			else if (!ft_check_export(*cmd))
			{
				ft_print_env_error("export: '", *cmd);
				g_out = 1;
			}
			cmd ++;
		}	
	}	
	return (local_env);
}

t_list	*ft_unset(char **cmd, t_list *local_env)
{
	int		i;
	char	*value;
	t_list	*tmp;

	i = 0;
	tmp = local_env;
	while (cmd[++i])
	{
		local_env = tmp;
		if (cmd[i] && (ft_strrchr(cmd[i], '=') || !ft_check_export(cmd[i])))
			ft_print_env_error("unset: '", cmd[i]);
		else
		{				
			value = ft_get_env_var_value(local_env, cmd[i]);
			if (value)
			{
				if (!ft_strncmp(tmp->content, cmd[i], ft_strlen(cmd[i])))
					tmp = ft_check_first_link(tmp, cmd[i], local_env);
				else
					ft_check_next_link(cmd[i], local_env);
				free(value);
			}
		}
	}
	return (tmp);
}

void	ft_env(char **cmd, t_list *local_env)
{
	if (cmd[1] != 0)
	{
		ft_putstr_fd("env: does not take arguments\n", 2);
		g_out = 1;
		return ;
	}
	ft_print_env(local_env, 1);
	g_out = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_functions_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:32:24 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/02 14:32:26 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_len_name_elem(char *elem)
{
	int	n;

	n = 0;
	if (elem == NULL)
		return (0);
	while (elem[n] != '=' && elem[n] != 0)
		n ++;
	return (n);
}

char	*ft_get_env_var_value(char *elem)
{
	int		start;
	int		len;
	char	*val;
	int		i;

	start = ft_len_name_elem(elem) + 1;
	len = ft_strlen(elem);
	val = malloc (sizeof(char) * (len - start + 1));
	i = 0;
	while (i < len - start)
	{
		val[i] = elem[start + i];
		i ++;
	}
	val [i] = '\0';
	return (val);
}

int	ft_is_already_in_env(t_list *local_env, char *elem)
{
	int		len;
	char	*tmp;

	len = ft_len_name_elem(elem);
	while (local_env)
	{		
		if (!ft_strncmp(local_env->content, elem, len))
		{	
			tmp = (char *)local_env->content;
			if (tmp[len] == '=')
			{
				local_env->content = elem;
				return (1);
			}
		}
		local_env = local_env->next;
	}
	return (0);
}

t_list	*ft_init_env(char **env)
{
	t_list	*local_env;
	int		i;

	local_env = NULL;
	i = 0;
	while (env[i])
		ft_lstadd_back(&local_env, ft_lstnew(env[i++]));
	return (local_env);
}

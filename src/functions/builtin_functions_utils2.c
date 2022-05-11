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

#include <minishell.h>
#include <built_in_functions.h>
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


char	*ft_get_env_var_value(t_list *local_env, char *elem)
{
	int		len;
	int		i;
	char	*val;
	char	*tmp;	

	len = ft_strlen(elem);
	while (local_env)
	{		
		if (!ft_strncmp(local_env->content, elem, len))
		{	
			tmp = (char *)local_env->content;
			if (tmp[len] == '=')
			{				
				val = malloc(sizeof(char) * (ft_strlen(tmp) - len + 1));
				i = 0;
				while (tmp[i + len + 1] != '\0')
				{
					val[i] = tmp[len + i + 1];
					i ++;
				}
				val[i] = '\0';
				return (val);
			}
		}
		local_env = local_env->next;
	}
	return (NULL);
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

t_list	*ft_check_next(char **cmd, t_list *local_env, int nb_cmd)
{
	char 	*c;
	int		i;

	i = 1;
	while (i < nb_cmd && local_env->next && local_env)
	{	
		c = (char *)local_env->next->content;
		if (cmd[i] && ft_strncmp(cmd[i], c, ft_strlen(cmd[i])) == 0 && c[ft_strlen(cmd[i])] == '=')
		{
			local_env->next->content = 0;
			free(local_env->next->content);
			if (local_env->next->next)
				local_env->next = local_env->next->next;
			else
				local_env->next = NULL;
		}		
		i ++;
	}
	return (local_env);
}

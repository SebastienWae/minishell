/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:32:24 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 15:41:23 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <unistd.h>

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
				val = ft_substr(tmp, len + 1, ft_strlen(tmp) - len + 1);
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
	char	*c;
	int		i;

	i = 1;
	while (i < nb_cmd && local_env->next && local_env)
	{	
		c = (char *)local_env->next->content;
		if (cmd[i] && ft_strncmp(cmd[i], c, ft_strlen(cmd[i])) == 0
			&& c[ft_strlen(cmd[i])] == '=')
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

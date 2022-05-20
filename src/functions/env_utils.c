/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:32:24 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/20 12:24:49 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

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

	len = 0;
	if (elem)
		while (elem[len] != '=' && elem[len] != 0)
			len++;
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

void	ft_print_env_error(char *function, char *id)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(function, 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

t_list	*ft_check_first_link(t_list *tmp, char *cmd, t_list *local_env)
{
	char	*name;

	name = (char *)tmp->content;
	if (name[ft_strlen(cmd)] == '=')
	{		
		ft_lstdelone(local_env, free);
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_check_next_link(char *cmd, t_list *local_env)
{
	char	*name;
	t_list	*tmp;

	while (local_env && local_env->next)
	{
		if (!ft_strncmp(local_env->next->content, cmd, ft_strlen(cmd)))
		{
			name = (char *)local_env->next->content;
			if (name[ft_strlen(cmd)] == '=')
			{
				tmp = local_env->next->next;
				ft_lstdelone(local_env->next, free);
				local_env->next = tmp;
			}
		}
		local_env = local_env->next;
	}
}

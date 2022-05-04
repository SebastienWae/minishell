/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:59:05 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/04 15:59:08 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*ft_init_env(char **env)
{
	t_list	*local_env;
	int		i;

	local_env = NULL;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("SHELL", env[i], 5))
			ft_lstadd_back(&local_env, ft_lstnew("SHELL=Minishell"));
		else
			ft_lstadd_back(&local_env, ft_lstnew(env[i]));
	}
	return (local_env);
}

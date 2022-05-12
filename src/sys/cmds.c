/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:43:27 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 15:47:37 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>
#include <utils.h>

int	ft_is_builtin_cmd(char *str)
{
	if (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

t_list	*ft_execute_builtin_cmd(char **parsed_str, t_list *local_env)
{
	if (ft_strcmp(parsed_str[0], "echo") == 0)
		ft_echo(parsed_str);
	else if (ft_strcmp(parsed_str[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(parsed_str[0], "cd") == 0)
		ft_cd(parsed_str, local_env);
	else if (ft_strcmp(parsed_str[0], "unset") == 0)
		local_env = ft_unset(parsed_str, local_env);
	else if (ft_strcmp(parsed_str[0], "export") == 0)
		local_env = ft_export(parsed_str, local_env);
	else if (ft_strcmp(parsed_str[0], "env") == 0)
		ft_env(parsed_str, local_env);
	return (local_env);
}

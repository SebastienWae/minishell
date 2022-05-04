/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:43:27 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/28 15:43:29 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <built_in_functions.h>
#include <stdio.h>

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
	if (ft_strcmp(parsed_str[0], "pwd") == 0)
		ft_pwd(parsed_str);
	if (ft_strcmp(parsed_str[0], "cd") == 0)
		ft_cd(parsed_str, local_env);
	if (ft_strcmp(parsed_str[0], "unset") == 0)
		local_env = ft_unset(parsed_str, local_env);
	if (ft_strcmp(parsed_str[0], "export") == 0)
		local_env = ft_export(parsed_str, local_env);
	if (ft_strcmp(parsed_str[0], "env") == 0)
		ft_env(parsed_str, local_env);
	return (local_env);
}

int	ft_print_env(t_list *local_env, int choice)
{
	while (local_env)
	{
		if (choice != 1)
			printf("declare -x ");
		printf("%s\n", (char *)local_env->content);
		local_env = local_env->next;
	}
	return(0);
}

int	ft_equal_is_in(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i ++;
	}
	return (0);
}

int	ft_check_char_export(char *str)
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

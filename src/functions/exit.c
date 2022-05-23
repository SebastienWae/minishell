/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/23 14:15:29 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>

static int	ft_exit_no_arg(char **str, t_minishell shell, t_parser *parsed)
{
	if (str[1] == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_lstclear(&shell.local_env, free);
		parsed->destroy(parsed);
		exit(0);
	}
	return (0);
}

static int	ft_exit_not_numeric_arg(char **str, t_minishell shell,
			t_parser *parsed)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_lstclear(&shell.local_env, free);
	parsed->destroy(parsed);
	exit(255);
}

static int ft_is_numeric_exit_code(char *str)
{

	int	i;
	i = 0;
	while (str[i] != '\0')
	{
		while (is_whitespace(str[i]))
			i ++;
		if (str[i] == '+' || str[i] == '-')
			i ++;
		while (is_whitespace(str[i]))
			i ++;
		while (str[i] != '\0')
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i ++;
		}
	}
	return (1);
}

int	ft_exit(char **str, t_minishell shell, t_parser *parsed)
{
	int	i;

	i = -1;
	ft_exit_no_arg(str, shell, parsed);
	if (!ft_is_numeric_exit_code(str[1]))
		ft_exit_not_numeric_arg(str, shell, parsed);
	if (str[2] != 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": exit: too many arguments\n", 2);
		g_out = 1;
		return (1);
	}
	i = ft_atoi(str[1]);
	parsed->destroy(parsed);
	ft_lstclear(&shell.local_env, free);
	exit((unsigned int)i);
}

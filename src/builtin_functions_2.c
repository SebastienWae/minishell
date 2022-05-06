/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:44:30 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/28 14:44:32 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <built_in_functions.h>
#include <stdio.h>

//ok
t_list	*ft_export(char **cmd, t_list *local_env)
{	
	char	*elem;
	int		i;

	i = 0;
	g_out = 0;
	if (cmd[1] == 0)
		ft_print_env(local_env, 2);
	else
		while (cmd[++i])
		{
			if (ft_check_char_export(cmd[i]) && ft_equal_is_in(cmd[i]))
			{
				elem = cmd[i];
				if (ft_is_already_in_env(local_env, elem) == 0)
					ft_lstadd_back(&local_env, ft_lstnew(elem));
			}
			else if (!ft_check_char_export(cmd[i]))
			{
				printf("export: %s: not a valid identifier\n", cmd[i]);
				g_out = 1;
			}
		}
	return (local_env);
}

// a laver
t_list	*ft_unset(char **cmd, t_list *local_env)
{
	t_list	*tmp;
	int		i;
	int		nb_cmd;
	char 	*c;

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
			if (cmd[i] && ft_strncmp(cmd[i], c, ft_strlen(cmd[i])) == 0 && c[ft_strlen(cmd[i])] == '=')
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
		local_env = ft_check_next (cmd, local_env, nb_cmd);
		local_env = local_env->next;
	}
	return (tmp);
}

// ne doit pas prendre d'argument cf sujet => sortie erreur a 1
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

//ok
int	ft_exit(char **str)
{
	int	i;

	i = 0;
	if (str[1] == 0)
	{
		printf("exit\n");
		exit (0);
	}
	while (str[1][i] != 0)
	{
		if (!ft_isdigit(str[1][i]))
		{
			printf("exit: %s: numeric argument required\n", str[1]);
			exit(255);
		}
		i ++;
	}		
	if (str[2] != 0)
	{
		printf("exit\nexit: too many arguments\n");
		return (0);
	}
	exit (ft_atoi(str[1]));
}

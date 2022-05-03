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

extern int g_out;

t_list	*ft_export(char **cmd, t_list *local_env)
{	
	t_list	*new;
	char	*elem;
	int		i;

	i = 0;
	g_out = 0;
	if (cmd[1] == 0)
		ft_print_env(local_env, 2);
	else if (cmd[1] != 0)
	{
		while (cmd[++i] != NULL)
		{
			if (ft_check_char_export(cmd[i]) && ft_equal_is_in(cmd[i]))
			{
				elem = cmd[i];
				if (ft_is_already_in_env(local_env, elem) == 0)
				{
					new = ft_lstnew(elem);
					ft_lstadd_back(&local_env, new);
				}
			}
			else if (!ft_check_char_export(cmd[i]))
			{
				printf("export: %s: not a valid identifier\n", cmd[i]);
				g_out = 1;
			}
		}
	}	
	return (local_env);
}

t_list	*ft_unset(char **cmd, t_list *local_env)
{
	int		i;
	t_list	*tmp;
	int 	nb_cmd;

	g_out = 0;
	nb_cmd = 0;
	while (cmd[nb_cmd])
		nb_cmd ++;
	tmp = local_env;
	if (cmd[1] == 0)
		return (local_env);
	while (local_env)
	{
		i = 1;
		while (i < nb_cmd && local_env)
		{
			if (cmd[i] && !ft_check_char_export(cmd[i]))
			{		
				printf("unset: %s: not a valid identifier\n", cmd[i]); // sortie 1
				cmd[i] = NULL;
				g_out = 1;
				i ++;
			}
			if (cmd[i] && ft_strncmp(cmd[i], (char *)local_env->content, ft_strlen(cmd[i])) == 0)
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
		i = 1;
		while (i < nb_cmd && local_env->next && local_env)
		{				
			if (cmd[i] && ft_strncmp(cmd[i], (char *)local_env->next->content, ft_strlen(cmd[i])) == 0)
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
		local_env = local_env->next;
	}
	return (tmp); //sortie 0 seulement si pas de sortie 1
}

int	ft_env(char **cmd, t_list *local_env)
{
	if (cmd[1] != 0)
		printf("****** Permission denied ? ******** -- a changer");
	ft_print_env(local_env, 1);
	return (0);
}

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

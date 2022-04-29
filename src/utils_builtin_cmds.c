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

#include "pipex.h"
#include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

int ft_is_builtin_cmd(char *str)
{
	if (ft_strcmp(str, "echo") == 0
	|| ft_strcmp(str, "cd") == 0
	|| ft_strcmp(str, "pwd") == 0
	|| ft_strcmp(str, "unset") == 0
	|| ft_strcmp(str, "env") == 0)
		return (1);
	return(0);
}

int	ft_execute_builtin_cmd(char **parsed_str, t_list **local_env)
{
	if (ft_strcmp(parsed_str[0], "echo") == 0)
		ft_echo(parsed_str);
	if (ft_strcmp(parsed_str[0], "pwd") == 0)    
		ft_pwd(parsed_str);  
	if (ft_strcmp(parsed_str[0], "cd") == 0)    
		ft_cd(parsed_str); 
	if (ft_strcmp(parsed_str[0], "unset") == 0)    
		ft_unset(parsed_str, local_env);  
	if (ft_strcmp(parsed_str[0], "export") == 0)    
		ft_export(parsed_str, local_env);
	return(0);
}

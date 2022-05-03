/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 13:46:33 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# define SHELL_NAME "minishell"

typedef struct s_elem_env	t_elem_env;

struct	s_elem_env
{
	char	*name;
	char	*content;
};

int		is_quote(char c);
int		is_metacharacter(char c);
int		is_whitespace(char c);

int		ft_strcmp(char *str1, char *str2);
int		ft_execute_sys_cmd(char **cmd, char **env);

t_list	*tokenizer(char *line);
void	free_tokens(t_list *tokens);

#endif

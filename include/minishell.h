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
int		ft_is_builtin_cmd(char *str);
int		ft_check_char_export(char *str);
int		ft_equal_is_in(char *str);
int		ft_pwd(char **cmd);
int		ft_echo(char **cmd);
int		ft_cd(char **cmd);
int		ft_env(char **cmd, t_list *g_local_env);
void	ft_print_env(t_list *g_local_env, int choice);
void	ft_check_arg_error(int argc);

t_list	*tokenizer(char *line);
void	free_tokens(t_list *tokens);

t_list	*ft_unset(char **cmd, t_list *g_local_env);
t_list	*ft_export(char **cmd, t_list *g_local_env);
t_list	*ft_execute_builtin_cmd(char **parsed_str, t_list *g_local_env);

#endif

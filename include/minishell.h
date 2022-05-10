/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 17:12:45 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <tokenizer.h>
# include <parser.h>
# include <libft.h>

# define SHELL_NAME "minishell"

typedef struct s_elem_env	t_elem_env;

struct	s_elem_env
{
	char	*name;
	char	*content;
};

/* Checks if the character is considered to be a whitespace.
Returns 1 if true, 0 if false. */
int			is_whitespace(char c);

/* Join two strings with a separator */
char		*ft_strjoin_sep(const char *s1, const char *s2, const char *sep);

/* Split and classify the given string.*/
t_tokenizer	*tokenize(char *line);

/* Parse a list of tokens into a list of cmds.*/
t_parser	*parse(t_tokenizer *tokenizer);

int			ft_strcmp(char *str1, char *str2);
int			ft_execute_sys_cmd(char **cmd, char **env);
int			ft_is_builtin_cmd(char *str);
int			ft_check_char_export(char *str);
int			ft_equal_is_in(char *str);
int			ft_pwd(char **cmd);
int			ft_echo(char **cmd);
int			ft_cd(char **cmd);
int			ft_env(char **cmd, t_list *g_local_env);
void		ft_print_env(t_list *g_local_env, int choice);
void		ft_check_arg_error(int argc);

t_list		*ft_unset(char **cmd, t_list *g_local_env);
t_list		*ft_export(char **cmd, t_list *g_local_env);
t_list		*ft_execute_builtin_cmd(char **parsed_str, t_list *g_local_env);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:20:47 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/03 16:20:49 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_FUNCTIONS_H
# define BUILT_IN_FUNCTIONS_H

# include <minishell.h>
# include <libft.h>

typedef struct s_unset {
	t_list *tmp;
	t_list *local_env;
}   t_unset;

int		ft_is_builtin_cmd(char *str);
t_list	*ft_execute_builtin_cmd(char **parsed_str, t_list *local_env);

/* Environment handling functions */

int		ft_equal_is_in(char *str);
int		ft_len_name_elem(char *elem);
int		ft_is_already_in_env(t_list *local_env, char *elem);
int		ft_print_env(t_list *local_env, int choice);
int		ft_check_char_export(char *str);
void	ft_env(char **cmd, t_list *local_env);
char	*ft_get_env_var_value(char *elem);
t_list	*ft_unset(char **cmd, t_list *local_env);
t_list	*ft_check_next(char **cmd, t_list *local_env, int nb_cmd);
t_list	*ft_export(char **cmd, t_list *local_env);

/* Others built-in functions */

int		ft_exit(char **str, t_minishell shell);
void	ft_pwd(char **cmd);
void	ft_echo(char **cmd);
void	ft_cd(char **cmd, t_list *local_env);

#endif
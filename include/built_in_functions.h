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

int		ft_is_builtin_cmd(char *str);
int		ft_check_char_export(char *str);
int		ft_equal_is_in(char *str);
int		ft_pwd(char **cmd);
int		ft_echo(char **cmd);
int		ft_cd(char **cmd);
int		ft_exit(char **str);
int		ft_env(char **cmd, t_list *local_env);
int		ft_len_name_elem(char *elem);
int		ft_is_already_in_env(t_list *local_env, char *elem);
void	ft_print_env(t_list *local_env, int choice);
t_list	*ft_unset(char **cmd, t_list *local_env);
t_list	*ft_export(char **cmd, t_list *local_env);
t_list	*ft_execute_builtin_cmd(char **parsed_str, t_list *local_env);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:20:47 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 15:45:10 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <minishell.h>
# include <libft.h>

typedef struct s_unset
{
	t_list	*tmp;
	t_list	*local_env;
}	t_unset;

void	ft_cd(char **cmd, t_list *local_env);
void	ft_echo(char **cmd);
int		ft_len_name_elem(char *elem);
char	*ft_get_env_var_value(t_list *local_env, char *elem);
int		ft_is_already_in_env(t_list *local_env, char *elem);
t_list	*ft_check_next(char **cmd, t_list *local_env, int nb_cmd);
t_list	*ft_export(char **cmd, t_list *local_env);
t_list	*ft_unset(char **cmd, t_list *local_env);
void	ft_env(char **cmd, t_list *local_env);
int		ft_exit(char **str, t_minishell shell);
void	ft_pwd(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:20:47 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/12 16:31:17 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <libft.h>
# include <minishell.h>

typedef struct s_unset
{
	t_list	*tmp;
	int		nb_cmd;
	int		i;
	char	*copy;
}			t_unset;

void	ft_cd(char **cmd, t_list *local_env);
void	ft_echo(char **cmd);
char	*ft_get_env_var_value(t_list *local_env, char *elem);
void	ft_print_env_error(char *function, char *id);
int		ft_is_already_in_env(t_list *local_env, char *elem);
t_list	*ft_export(char **cmd, t_list *local_env);
t_list	*ft_unset(char **cmd, t_list *local_env);
void	ft_check_next_link(char *cmd, t_list *local_env);
t_list	*ft_check_first_link(t_list *tmp, char *cmd, t_list *local_env);
void	ft_env(char **cmd, t_list *local_env);
int		ft_exit(char **str, t_minishell shell);
void	ft_pwd(void);

#endif

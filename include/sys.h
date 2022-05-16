/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:55:52 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/16 17:01:29 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_H
# define SYS_H

# include <libft.h>
# include <minishell.h>
# include <sys/_types/_pid_t.h>

char		*ft_search_path(char **env);
char		*ft_build_cmd(char **path, char *cmd);
int			*ft_execute_sys_cmd(char **cmd, t_list *local_env, char **env);
int			ft_sys_cmd_process(char **parsed_str, char *str, t_list *local_env, char **env);

int			ft_is_builtin_cmd(char *str);
t_list		*ft_execute_builtin_cmd(char **parsed_str, t_list *local_env);

void		ft_close_fd(t_minishell shell, int fd_in, int fd_out);
void		ft_close_saved_fd(t_minishell shell);
int			ft_heredoc_in(t_redir *redir);
t_fd_in_out	ft_fd_manager(t_cmd *cmd, int choice);
t_fd_in_out	ft_init_fd(void);
void		ft_fd_error (char *cmd);

void		ft_sig_handler(int sig);
void		ft_sig(void);
int			ft_ctrl_d_handler(char *str);

void		ft_launch_cmd(char *str, t_minishell shell, char **env);
t_minishell	ft_pipe(t_minishell shell, t_list *cmd, char **env);

#endif

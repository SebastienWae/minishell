/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:55:52 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 17:09:08 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_H
# define SYS_H

# include <libft.h>
# include <minishell.h>
# include <parser.h>
# include <expand.h>

typedef struct s_fd_in_out {
	int	in;
	int	out;
}	t_fd_in_out;

typedef struct s_heredoc {
	char		*input;
	char		*line;
	char		*word;
	int			fd_tmp;
	t_expand	*exp;
}	t_heredoc;

char		*ft_search_path(t_list *local_env);
char		*ft_build_cmd(char **path, char *cmd);
int			*ft_execute_sys_cmd(char **cmd, t_list *local_env);
int			ft_sys_cmd_process(char **cmd, t_list *l);
void		ft_free_path_list(char	**path_list);
void		ft_sys_cmd_error(char **cmd, char *main_cmd);

int			ft_is_builtin_cmd(char *str);
t_list		*ft_execute_builtin_cmd(char **parsed_str, t_list *local_env);

void		ft_reset_fd(t_minishell shell);
void		ft_close_saved_fd(t_minishell shell);
int			ft_heredoc_in(t_redir *redir, t_minishell shell);
t_fd_in_out	ft_fd_manager(t_cmd *cmd, int choice, t_minishell shell);
t_fd_in_out	ft_init_fd(void);
void		ft_fd_error(char *cmd);

void		ft_sig_handler(int sig);
void		ft_sig_hd_handle(int sig);
void		ft_sig(void);
int			ft_ctrl_d_handler(char *str, t_minishell shell);

void		ft_launch_cmd(char **cmd, t_minishell shell, t_parser *parsed);
t_minishell	ft_pipe(t_minishell shell, t_list *cmd);
t_minishell	ft_pipe_error(t_minishell shell, int choice);

#endif

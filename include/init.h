/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:31:33 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/03 16:31:35 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <libft.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <minishell.h>

/* Shell initialization */

void			ft_check_arg_error(int argc);
t_list			*ft_init_env(char **env);
t_minishell		ft_init_all(int argc, char **argv, char **env);
struct termios	ft_init_config(void);


/* Command initialization : init fd for this cmd & launch cmd */

void		ft_heredoc_in(char *cmd, t_minishell shell, char **env);
t_fd_in_out	ft_init_fd_minishell(void);
t_minishell	ft_launch_cmd(char *str, t_minishell shell, char **env);

#endif

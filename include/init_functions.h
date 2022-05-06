/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:31:33 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/03 16:31:35 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_FUNCTIONS_H
# define INIT_FUNCTIONS_H
# include <libft.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <termios.h>

typedef struct s_minishell {
	t_list			*local_env;
	struct termios	config;
	int 			saved_stdin;
	int 			saved_stdout;
} t_minishell;



void			ft_check_arg_error(int argc);
t_list			*ft_init_env(char **env);
struct termios	ft_init_config(void);
t_minishell		ft_init_all(int argc, char **argv, char **env);
t_fd_in_out		ft_init_fd_minishell(void);

#endif

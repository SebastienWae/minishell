/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 13:33:32 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <termios.h>

# define SHELL_NAME "minishell"

/* Global variable to save commands exit code */
extern int	g_out;

typedef struct s_minishell {
	t_list			*local_env;
	struct termios	config;
	int				saved_stdin;
	int				saved_stdout;
}	t_minishell;

#endif

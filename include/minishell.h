/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 13:54:09 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <tokenizer.h>
# include <parser.h>
# include <libft.h>
# include <termios.h>

# define SHELL_NAME "minishell"

/* Global variable to save commands exit code */
extern int	g_out;

typedef struct s_elem_env {
	char	*name;
	char	*content;
}	t_elem_env;

/* sets input and output for the current command */
typedef struct s_fd_in_out {
	int	in;
	int	out;
}	t_fd_in_out;

typedef struct s_minishell {
	t_list			*local_env;
	struct termios	config;
	int				saved_stdin;
	int				saved_stdout;
}	t_minishell;

/* Join two strings with a separator */
char		*ft_strjoin_sep(const char *s1, const char *s2, const char *sep);

/* Split and classify the given string.*/
t_tokenizer	*tokenize(char *line);

/* Parse a list of tokens into a list of cmds.*/
t_parser	*parse(t_tokenizer *tokenizer);

#endif

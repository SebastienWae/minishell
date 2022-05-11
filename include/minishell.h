/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/29 14:49:53 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <tokenizer.h>
# include <libft.h>
# include <termios.h>

# define SHELL_NAME "minishell"

/* Global variable to save commands exit code */
int	g_out;

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

/* Checks if the character is considered to be a whitespace.
Returns 1 if true, 0 if false. */
int			is_whitespace(char c);

/* Split and classify the given string.*/
t_tokenizer	*tokenize(char *line);

/* Some useful string functions not available in libft */
int			ft_strcmp(char *str1, char *str2);
char		*ft_strncpy(char *src, size_t index, size_t end);

/* Need this one for now but will be replaced by libft split later */
char		**ft_better_split(char *s, char c);

/* Command launching functions */
t_minishell	ft_pipe(t_minishell shell, char **env);
t_minishell	ft_launch_cmd(char *str, t_minishell shell, char **env);

#endif
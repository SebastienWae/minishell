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

# include <libft.h>
# include <termios.h>

int	g_out;

typedef struct s_cmd		t_cmd;
typedef struct s_in			t_in;
typedef struct s_out		t_out;
typedef struct s_token		t_token;
typedef struct s_elem_env	t_elem_env;
typedef enum e_in_type		t_in_type;
typedef enum e_out_type		t_out_type;
typedef enum e_token_type	t_token_type;
typedef union u_data		t_data;
typedef union u_token_data	t_token_data;

enum	e_in_type {
	IN_PIPE,
	IN_FILE,
	HEREDOC
};
enum	e_out_type {
	OUT_PIPE,
	OUT_FILE,
	OUT_FILE_APPEND,
	STD
};
enum e_token_type {
	METACHARACTER,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	WORD
};

union u_data {
	t_cmd	*pipe_src;
	char	*path;
};
union u_token_data {
	char	*word;
	char	c;
};

struct s_cmd {
	char	**cmd;
	t_list	*in;
	t_out	*out;
};
struct s_in {
	enum e_in_type	type;
	union u_data	*data;
};
struct s_out {
	enum e_out_type	type;
	union u_data	*data;
};
struct s_token {
	enum e_token_type	type;
	union u_token_data	data;
};

struct	s_elem_env
{
	char	*name;
	char	*content;
};



int		is_quote(char c);
int		is_metacharacter(char c);
int		is_whitespace(char c);
int		ft_strcmp(char *str1, char *str2);
int		ft_execute_sys_cmd(char **cmd, char **env);
void	ft_sys_cmd_process (char **parsed_str, char *str, char **env);
void	free_tokens(t_list *tokens);
char	*ft_get_env_var_value(char *elem);
t_list	*tokenizer(char *line);

#endif
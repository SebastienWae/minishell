/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/29 14:32:30 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

typedef struct s_cmd		t_cmd;
typedef struct s_in			t_in;
typedef struct s_out		t_out;
typedef enum e_in_type		t_in_type;
typedef enum e_out_type		t_out_type;
typedef union u_data		t_data;

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

union u_data {
	t_cmd	*pipe_src;
	char	*path;
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

int	is_metacharacter(char c);
int	is_whitespace(char c);
int	is_quote(char c);

#endif

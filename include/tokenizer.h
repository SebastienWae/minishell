/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 21:43:40 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_tokenizer_state		t_tokenizer_state;
typedef enum e_tokenizer_event		t_tokenizer_event;
typedef enum e_toke_type			t_token_type;
typedef struct s_tokenizer			t_tokenizer;
typedef struct s_tokenizer_events	t_tokenizer_events;
typedef struct s_tokenizer_states	t_tokenizer_states;
typedef struct s_token				t_token;

enum e_tokenizer_state
{
	S_T_NOT_TOKEN = 1,
	S_T_IN_WORD,
	S_T_IN_OPERATOR,
	S_T_IN_QUOTE,
	S_T_FINISHED
};

enum e_tokenizer_event
{
	E_T_CHAR = 1,
	E_T_OPERATOR,
	E_T_WHITESPACE,
	E_T_QUOTE,
	E_T_UNIMPLEMENTED,
};

enum e_toke_type
{
	T_T_WORD = 1,
	T_T_PIPE,
	T_T_HEREDOC,
	T_T_REDIRECTION_IN,
	T_T_REDIRECTION_OUT,
	T_T_REDIRECTION_APPEND,
	T_T_SINGLE_QUOTE_WORD,
	T_T_DOUBLE_QUOTE_WORD,
	T_T_SYNTAX_ERROR,
	T_T_UNIMPLEMENTED,
	T_T_NONE
};

struct s_tokenizer
{
	t_list				*tokens;
	char				*line;
	int					start_cursor;
	int					end_cursor;
	t_token_type		token_type;
	t_tokenizer_event	event;
	t_tokenizer_state	state;
};

struct s_tokenizer_events
{
	t_tokenizer_event	event;
	void				(*handler)(t_tokenizer *);
};

struct s_tokenizer_states
{
	t_tokenizer_state	state;
	void				(*handler)(t_tokenizer *);
};

struct s_token {
	t_token_type	type;
	char			*token;
	void			(*free)(t_token *);
};

t_tokenizer	*tokenizer_constructor(char *line);
t_token		*token_constructor(t_token_type type, char *token);

void		tokenizer_char_handler(t_tokenizer *t);
void		tokenizer_operator_handler(t_tokenizer *t);
void		tokenizer_whitespace_handler(t_tokenizer *t);
void		tokenizer_quote_handler(t_tokenizer *t);
void		tokenizer_unimplemented_handler(t_tokenizer *t);

#endif

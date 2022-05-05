/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 19:22:37 by seb              ###   ########.fr       */
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
	t_list				*list;
	char				*line;
	int					start_cursor;
	int					end_cursor;
	t_token_type		token_type;
	t_tokenizer_state	state;
	t_tokenizer_event	event;
	void				(*append_char)(t_tokenizer *, t_tokenizer_state, t_token_type);
	void				(*new_token)(t_tokenizer *, t_tokenizer_state, t_token_type);
	void				(*remove_char)(t_tokenizer *, t_tokenizer_state, t_token_type);
	void				(*delimit_token)(t_tokenizer *, t_tokenizer_state, t_token_type);
};

struct s_tokenizer_events
{
	t_tokenizer_event	event;
	void			(*handler)(t_tokenizer *);
};

struct s_tokenizer_states
{
	t_tokenizer_state	state;
	void			(*handler)(t_tokenizer *);
};

struct s_token {
	t_token_type	type;
	char			*token;
	void			(*free)(t_token *);
};

t_tokenizer	*tokenizer(char *line);
void		tokenizer_finish(t_tokenizer *tokens);
void		tokens_free(t_tokenizer *t);

void		tokenizer_state_not_token(t_tokenizer *t);
void		tokenizer_state_in_word(t_tokenizer *t);
void		tokenizer_state_in_operator(t_tokenizer *t);
void		tokenizer_state_in_quote(t_tokenizer *t);

void		tokenizer_operator(t_tokenizer *t);

t_tokenizer	*tokens_constructor(char *line);

t_token		*token_constructor(t_token_type type, char *token);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 13:45:52 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_token_state		t_token_state;
typedef enum e_token_event		t_token_event;
typedef enum e_toke_type		t_token_type;
typedef struct s_tokens			t_tokens;
typedef struct s_token			t_token;
typedef struct s_token_machine	t_token_machine;
typedef void					(*t_token_handler)(t_tokens *);

enum e_token_state
{
	S_T_NOT_TOKEN,
	S_T_IN_WORD,
	S_T_IN_OPERATOR,
	S_T_IN_QUOTE,
	S_T_FINISHED
};

enum e_token_event
{
	E_T_CHAR,
	E_T_OPERATOR,
	E_T_WHITESPACE,
	E_T_QUOTE,
	E_T_UNIMPLEMENTED,
	E_T_ERROR,
	E_T_END
};

enum e_toke_type
{
	T_T_WORD,
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

struct s_tokens
{
	t_list			*list;
	char			*line;
	int				start_cursor;
	int				end_cursor;
	t_token_type	curr_token_type;
	t_token_state	state;
	t_token_event	event;
	void			(*append_char)(t_tokens *, t_token_state);
	void			(*remove_char)(t_tokens *, t_token_state);
	void			(*delimit_token)(t_tokens *, t_token_state);
	void			(*free)(t_tokens *);
};

struct s_token_machine
{
	t_token_state	state;
	t_token_handler	handler;
};

struct s_token {
	t_token_type	type;
	char			*token;
	void			(*free)(t_token *);
};

t_tokens	*tokenizer(char *line);
void		tokenizer_next(t_tokens *t, t_token_event e);
void		tokenizer_finish(t_tokens *tokens);

void		tokenizer_state_not_token(t_tokens *t);
void		tokenizer_state_in_word(t_tokens *t);
void		tokenizer_state_in_operator(t_tokens *t);
void		tokenizer_state_in_quote(t_tokens *t);

void		tokenizer_operator(t_tokens *t);

t_tokens	*tokens_constructor(char *line);

t_token		*token_constructor(t_token_type type, char *token);

#endif

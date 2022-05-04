/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/04 21:53:58 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_token_state
{
	S_T_NOT_TOKEN,
	S_T_IN_WORD,
	S_T_IN_OPERATOR,
	S_T_IN_SINGLE_QUOTE,
	S_T_IN_DOUBLE_QUOTE,
	S_T_ERROR,
	S_T_FINISHED
}	t_token_state;

typedef enum e_token_event
{
	E_T_CHAR,
	E_T_OPERATOR,
	E_T_WHITESPACE,
	E_T_SINGLE_QUOTE,
	E_T_DOUBLE_QUOTE,
	E_T_UNIMPLEMENTED,
	E_T_ERROR,
	E_T_END
}	t_token_event;

typedef struct s_tokens	t_tokens;
typedef struct s_token	t_token;
typedef void			(*t_token_handler)(t_tokens *);
struct s_tokens
{
	t_list			*list;
	char			*line;
	int				start_cursor;
	int				end_cursor;
	char			*curr_token;
	t_token_state	state;
	t_token_event	last_event;
	void			(*append_char)(t_tokens *, t_token_state);
	void			(*remove_char)(t_tokens *, t_token_state);
	void			(*delimit_token)(t_tokens *, t_token_state);
	void			(*free)(t_tokens *);
};

typedef struct s_token_machine
{
	t_token_state	state;
	t_token_handler	handler;
}	t_token_machine;

typedef enum e_toke_type
{
	WORD,
	PIPE,
	HEREDOC,
	REDIRECTION,
	REDIRECTION_APPEND,
	SINGLE_QUOTE_WORD,
	DOUBLE_QUOTE_WORD,
}	t_token_type;

struct s_token {
	t_token_type	type;
	char			*token;
	void			(*free)(t_token *);
};

t_list		*tokenizer(char *line);
void		tokenizer_next(t_tokens *t, t_token_event e);

void		tokenizer_state_not_token(t_tokens *t);
void		tokenizer_state_in_word(t_tokens *t);
void		tokenizer_state_in_operator(t_tokens *t);
void		tokenizer_state_in_single_quote(t_tokens *t);
void		tokenizer_state_in_double_quote(t_tokens *t);

t_tokens	tokens_constructor(char *line);
t_token		token_constructor(t_token_type type, char *token);

#endif

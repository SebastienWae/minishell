/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:05:05 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 17:52:07 by swaegene         ###   ########.fr       */
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
typedef void			(*t_token_handler)(t_tokens *, t_token_event);
struct s_tokens
{
	t_list			*tokens;
	char			*line;
	int				start_cursor;
	int				end_cursor;
	char			*curr_token;
	t_token_state	state;
	void			(*append_char)(t_tokens *, t_token_state);
	void			(*remove_char)(t_tokens *, t_token_state);
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

typedef struct s_token {
	t_token_type	type;
	char			*token;
}	t_token;

void		tokenizer_next(t_tokens *t, t_token_event e);

t_tokens	tokens_constructor(char *line);

void		tokenizer_state_not_token(t_tokens *t, t_token_event e);
void		tokenizer_state_in_word(t_tokens *t, t_token_event e);
void		tokenizer_state_in_operator(t_tokens *t, t_token_event e);
void		tokenizer_state_in_single_quote(t_tokens *t, t_token_event e);
void		tokenizer_state_in_double_quote(t_tokens *t, t_token_event e);

#endif

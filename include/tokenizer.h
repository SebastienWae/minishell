/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:43:39 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 18:25:19 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_token_state
{
	ST_T_INIT,
	ST_T_IN_DOUBLE_QUOTE,
	ST_T_IN_SINGLE_QUOTE,
	ST_T_IN_WORD,
	ST_T_IN_METACHAR,
	ST_T_ERROR
}	t_token_state;

typedef enum e_token_event
{
	E_T_CHAR,
	E_T_METACHAR,
	E_T_WHITESPACE,
	E_T_DOUBLE_QUOTE,
	E_T_SINGLE_QUOTE
}	t_token_event;

typedef struct s_tokens
{
	t_list			*tokens;
	char			*line;
	int				cursor;
	char			*curr_word;
	t_token_state	state;
}	t_tokens;

typedef void	(*t_token_handler)(t_tokens *, t_token_event);

typedef struct s_token_machine
{
	t_token_state	state;
	t_token_handler	handler;
}	t_token_machine;

typedef enum e_toke_type
{
	METACHAR,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	WORD
}	t_token_type;

typedef union u_token_data
{
	char	*word;
	char	c;
}	t_token_data;

typedef struct s_token {
	t_token_type	type;
	t_token_data	data;
}	t_token;

void	tokenizer_next(t_tokens *t, t_token_event e);

void	*add_token(t_token_type t, t_token_data d, t_tokens *to);

void	tokenizer_in_metachar(t_tokens *t, t_token_event e);
void	tokenizer_in_word(t_tokens *t, t_token_event e);
void	tokenizer_in_single_quote(t_tokens *t, t_token_event e);
void	tokenizer_in_double_quote(t_tokens *t, t_token_event e);
void	tokenizer_init(t_tokens *t, t_token_event e);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:43:39 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 14:45:44 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <minishell.h>
# include <libft.h>

typedef enum e_token_state
{
	ST_T_INIT,
	ST_T_TOKENIZING,
	ST_T_IN_SINGLE_QUOTE,
	ST_T_IN_DOUBLE_QUOTE
}	t_token_state;

typedef enum e_token_event
{
	EV_T_WORD,
	EV_T_WHITESPACE,
	EV_T_METACHAR,
	EV_T_SINGLE_QUOTE,
	EV_T_DOUBLE_QUOTE
}	t_token_event;

typedef struct s_token_trans_matrix_row {
	t_token_state	curr_state;
	t_token_event	event;
	t_token_state	next_state;
}	t_token_trans_matrix_row;

typedef struct s_token_handler {
	const char	*name;
	void		(*f)(void);
}	t_token_handler;

#endif

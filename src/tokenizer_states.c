/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:52:40 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 20:30:07 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_state_not_token(t_tokens *t)
{
	if (t->last_event == E_T_CHAR)
		t->append_char(t, S_T_IN_WORD);
	else if (t->last_event == E_T_OPERATOR)
		t->append_char(t, S_T_IN_OPERATOR);
	else if (t->last_event == E_T_WHITESPACE)
		t->remove_char(t, S_T_NOT_TOKEN);
	else if (t->last_event == E_T_SINGLE_QUOTE)
		t->remove_char(t, S_T_IN_SINGLE_QUOTE);
	else if (t->last_event == E_T_DOUBLE_QUOTE)
		t->remove_char(t, S_T_IN_DOUBLE_QUOTE);
}

void	tokenizer_state_in_word(t_tokens *t);
void	tokenizer_state_in_operator(t_tokens *t);
void	tokenizer_state_in_single_quote(t_tokens *t);
void	tokenizer_state_in_double_quote(t_tokens *t);

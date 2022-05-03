/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:32:50 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 18:23:56 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_init(t_tokens *t, t_token_event event)
{
	if (event == E_T_CHAR)
	{
		t->curr_word = &(t->line[t->cursor]);
		t->state = ST_T_IN_WORD;
	}
	else if (event == E_T_METACHAR)
	{
		t->curr_word = &(t->line[t->cursor]);
		t->state = ST_T_IN_METACHAR;
	}
	else if (event == E_T_WHITESPACE)
		t->line[t->cursor] = 0;
	else if (event == E_T_DOUBLE_QUOTE)
	{
		t->line[t->cursor] = 0;
		t->state = ST_T_IN_DOUBLE_QUOTE;
	}
	else if (event == E_T_SINGLE_QUOTE)
	{
		t->line[t->cursor] = 0;
		t->state = ST_T_IN_SINGLE_QUOTE;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:55:08 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 16:32:18 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_whitespace_handler(t_tokenizer *t)
{
	if (t->curr_token)
	{
		if (t->curr_token->type != T_TT_DOUBLE_QUOTE_WORD
			&& t->curr_token->type != T_TT_SINGLE_QUOTE_WORD)
		{
			t->line[t->cursor] = 0;
			tokenizer_delimit_curr_token(t);
		}
	}
	t->cursor++;
}

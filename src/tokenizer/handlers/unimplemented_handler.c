/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unimplemented_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:54:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 12:13:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_unimplemented_handler(t_tokenizer *t)
{
	if (t->curr_token)
	{
		if (t->curr_token->type == T_TT_DOUBLE_QUOTE_WORD
			|| t->curr_token->type == T_TT_SINGLE_QUOTE_WORD)
			t->cursor++;
		else
		{
			tokenizer_delimit_and_new(t, T_TT_UNIMPLEMENTED);
			tokenizer_delimit_curr_token(t);
		}
	}
	else
	{
		tokenizer_new_token(t, T_TT_UNIMPLEMENTED);
		tokenizer_delimit_curr_token(t);
	}
	t->state = T_S_FINISHED;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:52:58 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 10:50:27 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_double_quote_handler(t_tokenizer *t)
{
	if (t->curr_token)
	{
		if (t->curr_token->type == T_TT_WORD)
		{
			t->curr_token->type = T_TT_DOUBLE_QUOTE_WORD;
			t->cursor++;
		}
		else if (t->curr_token->type == T_TT_SINGLE_QUOTE_WORD
			|| t->curr_token->type == T_TT_DOUBLE_QUOTE_WORD)
			t->cursor++;
		else if (t->curr_token->type == T_TT_PIPE
			|| t->curr_token->type == T_TT_HEREDOC
			|| t->curr_token->type == T_TT_REDIRECTION_IN
			|| t->curr_token->type == T_TT_REDIRECTION_OUT
			|| t->curr_token->type == T_TT_REDIRECTION_APPEND)
		{
			tokenizer_delimit_curr_token(t);
			tokenizer_new_token(t, T_TT_DOUBLE_QUOTE_WORD);
		}
	}
	else
		tokenizer_new_token(t, T_TT_DOUBLE_QUOTE_WORD);
}

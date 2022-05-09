/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:53:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/07 14:23:38 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_less_handler(t_tokenizer *t)
{
	static t_tokenizer_char_handlers	handlers[] = {
	{T_TT_WORD, tokenizer_delimit_new, T_TT_REDIRECTION_IN},
	{T_TT_PIPE, tokenizer_error_token, T_TT_SYNTAX_ERROR},
	{T_TT_HEREDOC, tokenizer_error_token, T_TT_SYNTAX_ERROR},
	{T_TT_REDIRECTION_IN, tokenizer_increase_cursor, T_TT_HEREDOC},
	{T_TT_REDIRECTION_OUT, tokenizer_error_token, T_TT_SYNTAX_ERROR},
	{T_TT_REDIRECTION_APPEND, tokenizer_error_token, T_TT_SYNTAX_ERROR},
	{T_TT_SINGLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_DOUBLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_DOUBLE_QUOTE_WORD}
	};

	if (t->curr_token)
	{
		if (t->curr_token->type == T_TT_WORD
			|| t->curr_token->type == T_TT_REDIRECTION_IN)
			t->line[t->cursor] = 0;
		handlers[t->curr_token->type - 1].handler(t,
			handlers[t->curr_token->type - 1].arg_type);
	}
	else
	{
		t->line[t->cursor] = 0;
		tokenizer_new_token(t, T_TT_REDIRECTION_IN);
	}
}

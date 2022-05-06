/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:54:42 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 16:01:26 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_single_quote_handler(t_tokenizer *t)
{
	static t_tokenizer_char_handlers	handlers[] = {
	{T_TT_WORD, tokenizer_increase_cursor, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_PIPE, tokenizer_delimit_new, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_HEREDOC, tokenizer_delimit_new, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_REDIRECTION_IN, tokenizer_delimit_new, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_REDIRECTION_OUT, tokenizer_delimit_new, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_REDIRECTION_APPEND, tokenizer_delimit_new, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_SINGLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_WORD},
	{T_TT_DOUBLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_SINGLE_QUOTE_WORD}
	};

	if (t->curr_token)
		handlers[t->curr_token->type - 1].handler(t,
			handlers[t->curr_token->type - 1].arg_type);
	else
		tokenizer_new_token(t, T_TT_SINGLE_QUOTE_WORD);
}

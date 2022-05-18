/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:49:58 by seb               #+#    #+#             */
/*   Updated: 2022/05/18 13:30:35 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_char_handler(t_tokenizer *t)
{
	static t_tokenizer_char_handlers	handlers[] = {
	{T_TT_WORD, tokenizer_increase_cursor, T_TT_WORD},
	{T_TT_PIPE, tokenizer_delimit_new, T_TT_WORD},
	{T_TT_HEREDOC, tokenizer_delimit_new, T_TT_WORD},
	{T_TT_REDIR_IN, tokenizer_delimit_new, T_TT_WORD},
	{T_TT_REDIR_OUT, tokenizer_delimit_new, T_TT_WORD},
	{T_TT_REDIR_APPEND, tokenizer_delimit_new, T_TT_WORD},
	{T_TT_SINGLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_SINGLE_QUOTE_WORD},
	{T_TT_DOUBLE_QUOTE_WORD, tokenizer_increase_cursor, T_TT_DOUBLE_QUOTE_WORD}
	};

	if (t->curr_token)
		handlers[t->curr_token->type - 1].handler(t,
			handlers[t->curr_token->type - 1].arg_type);
	else
		tokenizer_new_token(t, T_TT_WORD);
}

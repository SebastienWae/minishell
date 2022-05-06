/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unimplemented_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:54:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 17:03:24 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_unimplemented_handler(t_tokenizer *t)
{
	if (t->curr_token
		&& (t->curr_token->type == T_TT_DOUBLE_QUOTE_WORD
			|| t->curr_token->type == T_TT_SINGLE_QUOTE_WORD))
		t->cursor++;
	else
		tokenizer_error_token(t, T_TT_UNIMPLEMENTED);
}

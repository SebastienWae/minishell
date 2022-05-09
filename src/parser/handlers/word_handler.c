/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:49:12 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/09 18:01:02 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_word_handler(t_parser *p, t_token *t)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_add_to_cmd},
	{T_TT_PIPE, parser_new_cmd},
	{T_TT_HEREDOC, parser_set_heredoc_word},
	{T_TT_REDIRECTION_IN, parser_set_in},
	{T_TT_REDIRECTION_OUT, parser_set_out},
	{T_TT_REDIRECTION_APPEND, parser_set_append}
	};

	if (p->curr_cmd)
		handlers[p->last_token_type].handler(p, t);
	else
		parser_new_cmd(p, t);
}

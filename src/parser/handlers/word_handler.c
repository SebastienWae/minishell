/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:49:12 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/18 13:28:21 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_word_handler(t_parser *p)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_add_to_cmd},
	{T_TT_PIPE, parser_new_cmd},
	{T_TT_HEREDOC, parser_set_redir},
	{T_TT_REDIR_IN, parser_set_redir},
	{T_TT_REDIR_OUT, parser_set_redir},
	{T_TT_REDIR_APPEND, parser_set_redir}
	};

	if (p->curr_cmd)
		handlers[p->last_token_type - 1].handler(p);
	else
		parser_new_cmd(p);
	p->tokens = p->tokens->next;
}

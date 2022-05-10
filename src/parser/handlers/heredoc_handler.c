/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:07:43 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 20:07:08 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_heredoc_handler(t_parser *p, t_token *t)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_new_redir},
	{T_TT_PIPE, parser_new_redir},
	{T_TT_HEREDOC, parser_syntax_error},
	{T_TT_REDIRECTION_IN, parser_syntax_error},
	{T_TT_REDIRECTION_OUT, parser_syntax_error},
	{T_TT_REDIRECTION_APPEND, parser_syntax_error}
	};

	if (p->curr_cmd)
		handlers[p->last_token_type - 1].handler(p, t);
	else
		parser_new_cmd(p, t);
}

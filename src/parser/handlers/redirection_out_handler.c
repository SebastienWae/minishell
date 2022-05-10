/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:13:47 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 16:38:39 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_redirection_out_handler(t_parser *p, t_token *t)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_new_redir},
	{T_TT_PIPE, parser_error},
	{T_TT_HEREDOC, parser_error},
	{T_TT_REDIRECTION_IN, parser_error},
	{T_TT_REDIRECTION_OUT, parser_error},
	{T_TT_REDIRECTION_APPEND, parser_error}
	};

	if (p->curr_cmd)
		handlers[p->last_token_type].handler(p, t);
	else
		parser_new_cmd(p, t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:02:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/18 13:30:35 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_pipe_handler(t_parser *p)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_pipe_cmd},
	{T_TT_PIPE, parser_syntax_error},
	{T_TT_HEREDOC, parser_syntax_error},
	{T_TT_REDIR_IN, parser_syntax_error},
	{T_TT_REDIR_OUT, parser_syntax_error},
	{T_TT_REDIR_APPEND, parser_syntax_error}
	};

	if (p->curr_cmd)
		handlers[p->last_token_type - 1].handler(p);
	else
		parser_new_cmd(p);
	p->tokens = p->tokens->next;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append_handler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:14:56 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/09 18:15:40 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_redirection_append_handler(t_parser *p, t_token *t)
{
	static t_parser_token_handlers	handlers[] = {
	{T_TT_WORD, parser_redirection_append_handler},
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

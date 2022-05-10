/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:45 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 15:40:41 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_pipe_cmd(t_parser *p, t_token *t)
{
	p->curr_cmd->piped = 1;
	parser_end_cmd(p);
	p->last_token_type = t->type;
}

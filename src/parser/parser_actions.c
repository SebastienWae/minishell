/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:51:15 by seb               #+#    #+#             */
/*   Updated: 2022/05/20 14:04:38 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <stdio.h>
#include <tokenizer.h>

void	parser_pipe_cmd(t_parser *p)
{
	p->curr_cmd->piped = 1;
	parser_end_cmd(p);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_syntax_error(t_parser *p)
{
	printf(SHELL_NAME ": syntax error near unexpected token `%s'\n",
		((t_token *)p->tokens->content)->str);
	parser_end_cmd(p);
	p->state = P_S_ERROR;
}

void	parser_end(t_parser *p)
{
	parser_end_cmd(p);
	p->state = P_S_FINISHED;
}

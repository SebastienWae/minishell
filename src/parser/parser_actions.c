/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:51:15 by seb               #+#    #+#             */
/*   Updated: 2022/05/22 19:36:40 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdio.h>

void	parser_pipe_cmd(t_parser *p)
{
	p->curr_cmd->piped = 1;
	parser_end_cmd(p);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_syntax_error(t_parser *p)
{
	ft_putstr_fd(SHELL_NAME ": syntax error near unexpected token ", 2);
	ft_putstr_fd(((t_token *)p->tokens->content)->str, 2);
	ft_putstr_fd("\n", 2);
	parser_end_cmd(p);
	p->state = P_S_ERROR;
}

void	parser_end(t_parser *p)
{
	parser_end_cmd(p);
	p->state = P_S_FINISHED;
}

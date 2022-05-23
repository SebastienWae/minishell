/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:51:15 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 15:52:14 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <libft.h>
#include <parser.h>
#include <stdio.h>

void	parser_pipe_cmd(t_parser *p)
{
	p->curr_cmd->piped = 1;
	parser_end_cmd(p);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

static void	parser_print_token(t_parser *p)
{
	t_token	*t;

	t = p->tokens->content;
	if (t->type == T_TT_PIPE)
		ft_putstr_fd("|", 2);
	else if (t->type == T_TT_HEREDOC)
		ft_putstr_fd("<<", 2);
	else if (t->type == T_TT_REDIR_IN)
		ft_putstr_fd("<", 2);
	else if (t->type == T_TT_REDIR_OUT)
		ft_putstr_fd(">", 2);
	else if (t->type == T_TT_REDIR_APPEND)
		ft_putstr_fd(">>", 2);
}

void	parser_syntax_error(t_parser *p)
{
	ft_putstr_fd(SHELL_NAME ": syntax error near unexpected token `", 2);
	if (((t_token *)p->tokens->content)->type > 1
		&& ((t_token *)p->tokens->content)->type < 7)
		parser_print_token(p);
	else
		ft_putstr_fd(((t_token *)p->tokens->content)->str, 2);
	ft_putstr_fd("'\n", 2);
	parser_end_cmd(p);
	p->state = P_S_ERROR;
}

void	parser_end(t_parser *p)
{
	if (p->last_token_type > 1 && p->last_token_type < 7)
	{
		ft_putstr_fd(SHELL_NAME
			": syntax error near unexpected token `newline'\n", 2);
		parser_end_cmd(p);
		p->state = P_S_ERROR;
	}
	else
	{
		parser_end_cmd(p);
		p->state = P_S_FINISHED;
	}
}

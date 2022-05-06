/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:23:27 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 10:56:28 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

static void	tokenizer_op_pipe(t_tokenizer *t)
{
	if (t->line[t->cursor] == '|')
		t->token_type = T_T_UNIMPLEMENTED;
	else
		t->token_type = T_T_SYNTAX_ERROR;
	tokenizer_finish(t);
}

static void	tokenizer_op_heredoc(t_tokenizer *t)
{
	if (t->line[t->cursor] == '<')
		t->token_type = T_T_UNIMPLEMENTED;
	else
		t->token_type = T_T_SYNTAX_ERROR;
	tokenizer_finish(t);
}

static void	tokenizer_op_redir_in(t_tokenizer *t)
{
	if (t->line[t->cursor] == '<')
	{
		t->append_char(t, S_T_IN_OPERATOR, T_T_HEREDOC);
		t->token_type = T_T_HEREDOC;
	}
	else
	{
		if (t->line[t->cursor] == '>')
			t->token_type = T_T_UNIMPLEMENTED;
		else
			t->token_type = T_T_SYNTAX_ERROR;
		tokenizer_finish(t);
	}
}

static void	tokenizer_op_redir_out(t_tokenizer *t)
{
	if (t->line[t->cursor] == '>')
	{
		t->append_char(t, S_T_IN_OPERATOR, T_T_REDIRECTION_APPEND);
		t->token_type = T_T_REDIRECTION_APPEND;
	}
	else
	{
		if (t->line[t->cursor] == '|')
			t->token_type = T_T_UNIMPLEMENTED;
		else
			t->token_type = T_T_SYNTAX_ERROR;
		tokenizer_finish(t);
	}
}

void	tokenizer_operator(t_tokenizer *t)
{
	if (t->token_type == T_T_PIPE)
		tokenizer_op_pipe(t);
	else if (t->token_type == T_T_HEREDOC)
		tokenizer_op_heredoc(t);
	else if (t->token_type == T_T_REDIRECTION_IN)
		tokenizer_op_redir_in(t);
	else if (t->token_type == T_T_REDIRECTION_OUT)
		tokenizer_op_redir_out(t);
	else if (t->token_type == T_T_REDIRECTION_APPEND)
	{
		t->token_type = T_T_SYNTAX_ERROR;
		tokenizer_finish(t);
	}
}

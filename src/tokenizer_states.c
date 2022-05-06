/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:52:40 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/06 10:46:57 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_state_not_token(t_tokenizer *t)
{
	if (t->event == E_T_CHAR)
		t->append_char(t, S_T_IN_WORD, T_T_WORD);
	else if (t->event == E_T_OPERATOR)
	{
		if (t->line[t->cursor] == '|')
			t->remove_char(t, S_T_IN_OPERATOR, T_T_PIPE);
		else if (t->line[t->cursor] == '<')
			t->remove_char(t, S_T_IN_OPERATOR, T_T_REDIRECTION_IN);
		else if (t->line[t->cursor] == '>')
			t->remove_char(t, S_T_IN_OPERATOR, T_T_REDIRECTION_OUT);
	}
	else if (t->event == E_T_WHITESPACE)
		t->remove_char(t, S_T_NOT_TOKEN, T_T_NONE);
	else if (t->event == E_T_QUOTE)
	{
		if (t->line[t->cursor] == '\'')
			t->append_char(t, S_T_IN_QUOTE, T_T_SINGLE_QUOTE_WORD);
		else if (t->line[t->cursor] == '"')
			t->append_char(t, S_T_IN_QUOTE, T_T_DOUBLE_QUOTE_WORD);
	}
	else if (t->event == E_T_UNIMPLEMENTED)
	{
		t->token_type = T_T_UNIMPLEMENTED;
		tokenizer_finish(t);
	}
}

void	tokenizer_state_in_word(t_tokenizer *t)
{
	if (t->event == E_T_CHAR)
		t->append_char(t, S_T_IN_WORD, T_T_WORD);
	else if (t->event == E_T_OPERATOR)
	{
		if (t->line[t->cursor] == '|')
			t->delimit_token(t, S_T_IN_OPERATOR, T_T_PIPE);
		else if (t->line[t->cursor] == '<')
			t->delimit_token(t, S_T_IN_OPERATOR, T_T_REDIRECTION_IN);
		else if (t->line[t->cursor] == '>')
			t->delimit_token(t, S_T_IN_OPERATOR, T_T_REDIRECTION_OUT);
	}
	else if (t->event == E_T_WHITESPACE)
		t->delimit_token(t, S_T_NOT_TOKEN, T_T_NONE);
	else if (t->event == E_T_QUOTE)
	{
		if (t->line[t->cursor] == '\'')
			t->append_char(t, S_T_IN_QUOTE, T_T_SINGLE_QUOTE_WORD);
		else if (t->line[t->cursor] == '"')
			t->append_char(t, S_T_IN_QUOTE, T_T_DOUBLE_QUOTE_WORD);
	}
	else if (t->event == E_T_UNIMPLEMENTED)
	{
		t->new_token(t, S_T_IN_WORD, T_T_UNIMPLEMENTED);
		tokenizer_finish(t);
	}
}

void	tokenizer_state_in_operator(t_tokenizer *t)
{
	if (t->event == E_T_CHAR)
		t->new_token(t, S_T_IN_WORD, T_T_WORD);
	else if (t->event == E_T_OPERATOR)
		tokenizer_operator(t);
	else if (t->event == E_T_WHITESPACE)
		t->delimit_token(t, S_T_NOT_TOKEN, T_T_NONE);
	else if (t->event == E_T_QUOTE)
	{
		if (t->line[t->cursor] == '\'')
			t->new_token(t, S_T_IN_QUOTE, T_T_SINGLE_QUOTE_WORD);
		else if (t->line[t->cursor] == '"')
			t->new_token(t, S_T_IN_QUOTE, T_T_DOUBLE_QUOTE_WORD);
	}
	else if (t->event == E_T_UNIMPLEMENTED)
	{
		t->new_token(t, S_T_IN_WORD, T_T_UNIMPLEMENTED);
		tokenizer_finish(t);
	}
}

void	tokenizer_state_in_quote(t_tokenizer *t)
{
	t_token_type	type;

	type = t->token_type;
	if (t->event == E_T_CHAR || t->event == E_T_OPERATOR
		|| t->event == E_T_WHITESPACE || t->event == E_T_UNIMPLEMENTED)
		t->append_char(t, S_T_IN_QUOTE, type);
	else if (t->event == E_T_QUOTE)
	{
		if (t->token_type == T_T_DOUBLE_QUOTE_WORD)
		{
			if (t->line[t->cursor] == '\'')
				t->append_char(t, S_T_IN_QUOTE, type);
			else if (t->line[t->cursor] == '"')
				t->append_char(t, S_T_IN_WORD, T_T_WORD);
		}
		else if (t->token_type == T_T_SINGLE_QUOTE_WORD)
		{
			if (t->line[t->cursor] == '\'')
				t->append_char(t, S_T_IN_WORD, T_T_WORD);
			else if (t->line[t->cursor] == '"')
				t->append_char(t, S_T_IN_QUOTE, type);
		}
	}
}

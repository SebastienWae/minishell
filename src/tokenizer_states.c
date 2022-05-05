/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:52:40 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/05 11:02:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_state_not_token(t_tokens *t)
{
	if (t->event == E_T_CHAR)
	{
		t->append_char(t, S_T_IN_WORD);
		t->curr_token_type = T_T_WORD;
	}
	else if (t->event == E_T_OPERATOR)
	{
		t->append_char(t, S_T_IN_OPERATOR);
		if (t->line[t->end_cursor] == '|')
			t->curr_token_type = T_T_PIPE;
		else if (t->line[t->end_cursor] == '<')
			t->curr_token_type = T_T_REDIRECTION_IN;
		else if (t->line[t->end_cursor] == '>')
			t->curr_token_type = T_T_REDIRECTION_OUT;
	}
	else if (t->event == E_T_WHITESPACE)
		t->remove_char(t, S_T_NOT_TOKEN);
	else if (t->event == E_T_QUOTE)
	{
		t->append_char(t, S_T_IN_QUOTE);
		if (t->line[t->end_cursor] == '\'')
			t->curr_token_type = T_T_SINGLE_QUOTE_WORD;
		else if (t->line[t->end_cursor] == '"')
			t->curr_token_type = T_T_DOUBLE_QUOTE_WORD;
	}
}

void	tokenizer_state_in_word(t_tokens *t)
{
	if (t->event == E_T_CHAR)
		t->append_char(t, S_T_IN_WORD);
	else if (t->event == E_T_OPERATOR)
	{
		t->delimit_token(t, S_T_IN_OPERATOR);
		if (t->line[t->end_cursor] == '|')
			t->curr_token_type = T_T_PIPE;
		else if (t->line[t->end_cursor] == '<')
			t->curr_token_type = T_T_REDIRECTION_IN;
		else if (t->line[t->end_cursor] == '>')
			t->curr_token_type = T_T_REDIRECTION_OUT;
	}
	else if (t->event == E_T_WHITESPACE)
	{
		t->delimit_token(t, S_T_NOT_TOKEN);
		t->curr_token_type = T_T_NONE;
	}
	else if (t->event == E_T_QUOTE)
	{
		t->append_char(t, S_T_IN_QUOTE);
		if (t->line[t->end_cursor] == '\'')
			t->curr_token_type = T_T_SINGLE_QUOTE_WORD;
		else if (t->line[t->end_cursor] == '"')
			t->curr_token_type = T_T_DOUBLE_QUOTE_WORD;
	}
}

void	tokenizer_state_in_operator(t_tokens *t)
{
	if (t->event == E_T_CHAR)
	{
		t->delimit_token(t, S_T_IN_WORD);
		t->curr_token_type = T_T_WORD;
	}
	else if (t->event == E_T_OPERATOR)
		tokenizer_operator(t);
	else if (t->event == E_T_WHITESPACE)
	{
		t->delimit_token(t, S_T_NOT_TOKEN);
		t->curr_token_type = T_T_NONE;
	}
	else if (t->event == E_T_QUOTE)
	{
		t->delimit_token(t, S_T_IN_QUOTE);
		if (t->line[t->end_cursor] == '\'')
			t->curr_token_type = T_T_SINGLE_QUOTE_WORD;
		else if (t->line[t->end_cursor] == '"')
			t->curr_token_type = T_T_DOUBLE_QUOTE_WORD;
	}
}

void	tokenizer_state_in_quote(t_tokens *t)
{
	(void)t;
}

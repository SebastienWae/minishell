/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/05 10:45:52 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>

void	tokenizer_finish(t_tokens *t)
{
	t_token	token;

	token = token_constructor(t->curr_token_type, &(t->line[t->start_cursor]));
	if (t->list)
		ft_lstadd_back(&(t->list), ft_lstnew(&token));
	else
		t->list = ft_lstnew(&token);
	while (t->line[t->end_cursor] && !is_whitespace(t->line[t->end_cursor]))
		t->end_cursor++;
	t->line[t->end_cursor] = '\0';
	t->state = S_T_FINISHED;
}

void	tokenizer_next(t_tokens *tokens, t_token_event e)
{
	static t_token_machine	state_machine[] = {
	{.state = S_T_NOT_TOKEN,	.handler = tokenizer_state_not_token},
	{.state = S_T_IN_WORD,		.handler = tokenizer_state_in_word},
	{.state = S_T_IN_OPERATOR,	.handler = tokenizer_state_in_operator},
	{.state = S_T_IN_QUOTE,		.handler = tokenizer_state_in_quote},
	{.state = S_T_FINISHED,		.handler = tokenizer_finish},
	};

	tokens->event = e;
	if (e == E_T_UNIMPLEMENTED)
	{
		tokens->curr_token_type = T_T_UNIMPLEMENTED;
		tokenizer_finish(tokens);
	}
	else if (sizeof(state_machine) > tokens->state)
		state_machine[tokens->state].handler(tokens);
	else
		tokenizer_finish(tokens);
}

t_list	*tokenizer(char *line)
{
	t_tokens		tokens;

	tokens = tokens_constructor(line);
	while (tokens.state != S_T_FINISHED)
	{
		if (tokens.line[tokens.end_cursor] == '\0')
			tokenizer_next(&tokens, E_T_END);
		else if (is_quote(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_QUOTE);
		else if (is_operator(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_OPERATOR);
		else if (is_whitespace(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_WHITESPACE);
		else if (is_unimplemented(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_UNIMPLEMENTED);
		else
			tokenizer_next(&tokens, E_T_CHAR);
	}
	return (tokens.list);
}

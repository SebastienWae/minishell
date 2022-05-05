/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/05 19:21:34 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>

void	tokenizer_finish(t_tokenizer *t)
{
	t_token	*token;

	if (t->token_type != T_T_NONE)
	{
		token = token_constructor(t->token_type, &(t->line[t->start_cursor]));
		if (t->list)
			ft_lstadd_back(&(t->list), ft_lstnew(token));
		else
			t->list = ft_lstnew(token);
		while (t->line[t->end_cursor] && !is_whitespace(t->line[t->end_cursor]))
			t->end_cursor++;
		t->line[t->end_cursor] = '\0';
	}
	t->state = S_T_FINISHED;
}

void	tokens_free(t_tokenizer *t)
{
	t_list	*tmp;

	while (t->list)
	{
		tmp = t->list->next;
		((t_token *)(t->list->content))->free((t_token *)(t->list->content));
		t->list = tmp;
	}
	*t = (t_tokenizer)
	{
		.list = NULL,
		.start_cursor = 0,
		.end_cursor = 0,
		.line = NULL,
		.state = 0,
		.event = 0,
		.append_char = NULL,
		.new_token = NULL,
		.remove_char = NULL,
		.delimit_token = NULL,
	};
	free(t);
}

static void	tokenizer_event_handler(t_tokenizer *tokens, t_tokenizer_event e)
{
	static t_tokenizer_events	tokenizer_events[] = {
	{.event = E_T_CHAR,				.handler = tokenizer_char_handler},
	{.event = E_T_OPERATOR,			.handler = tokenizer_char_handler},
	{.event = E_T_WHITESPACE,		.handler = tokenizer_char_handler},
	{.event = E_T_QUOTE,			.handler = tokenizer_char_handler},
	{.event = E_T_UNIMPLEMENTED,	.handler = tokenizer_char_handler},
	};

	tokens->event = e;
	if (sizeof(tokenizer_events) > tokens->state)
		tokenizer_events[tokens->state].handler(tokens);
	else
		tokenizer_finish(tokens);
}

t_tokenizer	*tokenizer(char *line)
{
	t_tokenizer		*tokens;

	tokens = tokens_constructor(line);
	while (tokens->state != S_T_FINISHED)
	{
		if (tokens->line[tokens->end_cursor] == '\0')
			tokenizer_event_handler(tokens, 0);
		else if (is_quote(tokens->line[tokens->end_cursor]))
			tokenizer_event_handler(tokens, E_T_QUOTE);
		else if (is_operator(tokens->line[tokens->end_cursor]))
			tokenizer_event_handler(tokens, E_T_OPERATOR);
		else if (is_whitespace(tokens->line[tokens->end_cursor]))
			tokenizer_event_handler(tokens, E_T_WHITESPACE);
		else if (is_unimplemented(tokens->line[tokens->end_cursor]))
			tokenizer_event_handler(tokens, E_T_UNIMPLEMENTED);
		else
			tokenizer_event_handler(tokens, E_T_CHAR);
	}
	return (tokens);
}

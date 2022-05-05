/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/05 21:45:07 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>

static void	tokenizer_event_handler(t_tokenizer *tokens, t_tokenizer_event e)
{
	static t_tokenizer_events	tokenizer_events[] = {
	{.event = E_T_CHAR,				.handler = tokenizer_char_handler},
	{.event = E_T_OPERATOR,			.handler = tokenizer_operator_handler},
	{.event = E_T_WHITESPACE,		.handler = tokenizer_whitespace_handler},
	{.event = E_T_QUOTE,			.handler = tokenizer_quote_handler},
	{.event = E_T_UNIMPLEMENTED,	.handler = tokenizer_unimplemented_handler},
	};

	tokens->event = e;
	if (sizeof(tokenizer_events) > tokens->state)
		tokenizer_events[tokens->state].handler(tokens);
	else
		tokenizer_finish(tokens);
}

t_tokenizer	*tokenizer(char *line)
{
	t_tokenizer		*tokenizer;

	tokenizer = tokenizer_constructor(line);
	while (tokenizer->state != S_T_FINISHED)
	{
		if (tokenizer->line[tokenizer->end_cursor] == '\0')
			tokenizer_event_handler(tokenizer, 0);
		else if (is_quote(tokenizer->line[tokenizer->end_cursor]))
			tokenizer_event_handler(tokenizer, E_T_QUOTE);
		else if (is_operator(tokenizer->line[tokenizer->end_cursor]))
			tokenizer_event_handler(tokenizer, E_T_OPERATOR);
		else if (is_whitespace(tokenizer->line[tokenizer->end_cursor]))
			tokenizer_event_handler(tokenizer, E_T_WHITESPACE);
		else if (is_unimplemented(tokenizer->line[tokenizer->end_cursor]))
			tokenizer_event_handler(tokenizer, E_T_UNIMPLEMENTED);
		else
			tokenizer_event_handler(tokenizer, E_T_CHAR);
	}
	return (tokenizer);
}

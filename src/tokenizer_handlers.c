/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:14:50 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 19:21:30 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_char_handler(t_tokenizer *t)
{
	static t_tokenizer_states	tokenizer_states[] = {
	{.state = S_T_NOT_TOKEN,	.handler = NULL},
	{.state = S_T_IN_WORD,		.handler = NULL},
	{.state = S_T_IN_OPERATOR,	.handler = NULL},
	{.state = S_T_IN_QUOTE,		.handler = NULL},
	{.state = S_T_FINISHED,		.handler = NULL},
	};

	if (sizeof(tokenizer_states) > t->state)
		tokenizer_states[t->state].handler(t);
	else
		tokenizer_finish(t);
}

void	tokenizer_operator_handler(t_tokenizer *t)
{
	static t_tokenizer_states	tokenizer_states[] = {
	{.state = S_T_NOT_TOKEN,	.handler = NULL},
	{.state = S_T_IN_WORD,		.handler = NULL},
	{.state = S_T_IN_OPERATOR,	.handler = NULL},
	{.state = S_T_IN_QUOTE,		.handler = NULL},
	{.state = S_T_FINISHED,		.handler = NULL},
	};

	if (sizeof(tokenizer_states) > t->state)
		tokenizer_states[t->state].handler(t);
	else
		tokenizer_finish(t);
}

void	tokenizer_whitespace_handler(t_tokenizer *t)
{
	static t_tokenizer_states	tokenizer_states[] = {
	{.state = S_T_NOT_TOKEN,	.handler = NULL},
	{.state = S_T_IN_WORD,		.handler = NULL},
	{.state = S_T_IN_OPERATOR,	.handler = NULL},
	{.state = S_T_IN_QUOTE,		.handler = NULL},
	{.state = S_T_FINISHED,		.handler = NULL},
	};

	if (sizeof(tokenizer_states) > t->state)
		tokenizer_states[t->state].handler(t);
	else
		tokenizer_finish(t);
}

void	tokenizer_quote_handler(t_tokenizer *t)
{
	static t_tokenizer_states	tokenizer_states[] = {
	{.state = S_T_NOT_TOKEN,	.handler = NULL},
	{.state = S_T_IN_WORD,		.handler = NULL},
	{.state = S_T_IN_OPERATOR,	.handler = NULL},
	{.state = S_T_IN_QUOTE,		.handler = NULL},
	{.state = S_T_FINISHED,		.handler = NULL},
	};

	if (sizeof(tokenizer_states) > t->state)
		tokenizer_states[t->state].handler(t);
	else
		tokenizer_finish(t);
}

void	tokenizer_unimplemented_handler(t_tokenizer *t)
{
	static t_tokenizer_states	tokenizer_states[] = {
	{.state = S_T_NOT_TOKEN,	.handler = NULL},
	{.state = S_T_IN_WORD,		.handler = NULL},
	{.state = S_T_IN_OPERATOR,	.handler = NULL},
	{.state = S_T_IN_QUOTE,		.handler = NULL},
	{.state = S_T_FINISHED,		.handler = NULL},
	};

	if (sizeof(tokenizer_states) > t->state)
		tokenizer_states[t->state].handler(t);
	else
		tokenizer_finish(t);
}

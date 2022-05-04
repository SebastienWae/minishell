/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:33:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 21:53:11 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <stdlib.h>

static void	tokens_append_char(t_tokens *t, t_token_state s)
{
	t->curr_token = &(t->line[t->end_cursor]);
	t->state = s;
	t->end_cursor++;
}

static void	tokens_remove_char(t_tokens *t, t_token_state s)
{
	t->line[t->end_cursor] = 0;
	t->state = s;
	t->end_cursor++;
	t->start_cursor = t->end_cursor;
}

// TODO: implement
static void	tokens_delimit_token(t_tokens *t, t_token_state s)
{
	t->state = s;
	t->end_cursor++;
	t->start_cursor = t->end_cursor;
}

static void	tokens_free(t_tokens *t)
{
	t_list	*tmp;

	while (t->list)
	{
		tmp = t->list->next;
		((t_token *)(t->list->content))->free((t_token *)(t->list->content));
		free(t->list->content);
		t->list = tmp;
	}
	*t = (t_tokens)
	{
		.list = NULL,
		.start_cursor = 0,
		.end_cursor = 0,
		.line = NULL,
		.state = 0,
		.last_event = 0,
		.append_char = NULL,
		.remove_char = NULL,
		.delimit_token = NULL,
		.free = NULL
	};
	free(t);
}

t_tokens	tokens_constructor(char *line)
{
	return ((t_tokens)
		{
			.list = NULL,
			.start_cursor = 0,
			.end_cursor = 0,
			.line = line,
			.state = S_T_NOT_TOKEN,
			.last_event = 0,
			.append_char = tokens_append_char,
			.remove_char = tokens_remove_char,
			.delimit_token = tokens_delimit_token,
			.free = tokens_free
		});
}

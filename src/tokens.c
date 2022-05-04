/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:33:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 17:52:58 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

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

t_tokens	tokens_constructor(char *line)
{
	return ((t_tokens)
		{
			.tokens = NULL,
			.start_cursor = 0,
			.end_cursor = 0,
			.line = line,
			.state = S_T_NOT_TOKEN,
			.append_char = tokens_append_char,
			.remove_char = tokens_remove_char
		});
}

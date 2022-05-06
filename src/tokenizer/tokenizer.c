/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/06 14:26:00 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>
#include <stdlib.h>

static void	tokenizer_free(t_tokenizer *t)
{
	t_list	*tmp;

	while (t->tokens)
	{
		tmp = t->tokens->next;
		((t_token *)t->tokens->content)->free(t->tokens->content);
		t->tokens = tmp;
	}
	free(t->curr_token);
	*t = (t_tokenizer)
	{
		.tokens = NULL,
		.line = NULL,
		.cursor = 0,
		.curr_token = NULL,
		.state = 0,
		.free = NULL
	};
	free(t);
}

static t_tokenizer	*tokenizer_constructor(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	*tokenizer = (t_tokenizer)
	{
		.tokens = NULL,
		line,
		.cursor = 0,
		.curr_token = NULL,
		.state = T_S_WORKING,
		.free = tokenizer_free
	};
	return (tokenizer);
}

t_tokenizer	*tokenizer(char *line)
{
	t_tokenizer		*tokenizer;

	tokenizer = tokenizer_constructor(line);
	while (tokenizer && tokenizer->state != T_S_FINISHED)
	{
		if (tokenizer->line[tokenizer->cursor] == '\0')
			tokenizer_end_handler(tokenizer);
		else if (tokenizer->line[tokenizer->cursor] == '\'')
			tokenizer_single_quote_handler(tokenizer);
		else if (tokenizer->line[tokenizer->cursor] == '"')
			tokenizer_double_quote_handler(tokenizer);
		else if (tokenizer->line[tokenizer->cursor] == '|')
			tokenizer_pipe_handler(tokenizer);
		else if (tokenizer->line[tokenizer->cursor] == '<')
			tokenizer_less_handler(tokenizer);
		else if (tokenizer->line[tokenizer->cursor] == '>')
			tokenizer_great_handler(tokenizer);
		else if (is_whitespace(tokenizer->line[tokenizer->cursor]))
			tokenizer_whitespace_handler(tokenizer);
		else if (is_unimplemented(tokenizer->line[tokenizer->cursor]))
			tokenizer_unimplemented_handler(tokenizer);
		else
			tokenizer_char_handler(tokenizer);
	}
	return (tokenizer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/07 22:06:35 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>
#include <stdlib.h>

static void	token_destructor(t_token *self)
{
	*self = (t_token)
	{
		.str = NULL,
		.type = 0,
		.destructor = NULL
	};
	free(self);
}

t_token	*token_constructor(t_token_type type, char *str)
{
	t_token	*self;

	self = malloc(sizeof(t_token));
	if (!self)
		return (NULL);
	*self = (t_token)
	{
		str,
		type,
		.destructor = token_destructor
	};
	return (self);
}

static void	tokenizer_destructor(t_tokenizer *self)
{
	t_list	*tmp;

	while (self->tokens)
	{
		tmp = self->tokens->next;
		((t_token *)self->tokens->content)->destructor(self->tokens->content);
		free(self->tokens);
		self->tokens = tmp;
	}
	free(self->curr_token);
	*self = (t_tokenizer)
	{
		.tokens = NULL,
		.line = NULL,
		.cursor = 0,
		.curr_token = NULL,
		.state = 0,
		.destructor = NULL
	};
	free(self);
}

static t_tokenizer	*tokenizer_constructor(char *line)
{
	t_tokenizer	*self;

	self = malloc(sizeof(t_tokenizer));
	if (!self)
		return (NULL);
	*self = (t_tokenizer)
	{
		.tokens = NULL,
		line,
		.cursor = 0,
		.curr_token = NULL,
		.state = T_S_WORKING,
		.destructor = tokenizer_destructor
	};
	return (self);
}

t_tokenizer	*tokenize(char *line)
{
	t_tokenizer		*tokenizer;

	tokenizer = tokenizer_constructor(line);
	while (tokenizer && tokenizer->state == T_S_WORKING)
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
		else
			tokenizer_char_handler(tokenizer);
	}
	return (tokenizer);
}

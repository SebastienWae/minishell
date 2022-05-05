/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:33:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/05 21:45:04 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <tokenizer.h>
#include <stdlib.h>

static void	tokens_new_token(t_tokenizer *t, t_tokenizer_state s, t_token_type type)
{
	t_token		*token;

	token = token_constructor(t->token_type, &(t->line[t->start_cursor]));
	if (t->tokens)
		ft_lstadd_back(&(t->tokens), ft_lstnew(token));
	else
		t->tokens = ft_lstnew(token);
	t->token_type = type;
	t->state = s;
	t->start_cursor = t->end_cursor;
	t->end_cursor++;
}

static void	tokens_append_char(t_tokenizer *t, t_tokenizer_state s, t_token_type type)
{
	t->state = s;
	t->token_type = type;
	t->end_cursor++;
}

static void	tokens_remove_char(t_tokenizer *t, t_tokenizer_state s, t_token_type type)
{
	t->line[t->end_cursor] = 0;
	t->state = s;
	t->token_type = type;
	t->end_cursor++;
	t->start_cursor = t->end_cursor;
}

static void	tokens_delimit_token(t_tokenizer *t, t_tokenizer_state s, t_token_type ty)
{
	t_token		*token;

	token = token_constructor(t->token_type, &(t->line[t->start_cursor]));
	if (t->tokens)
		ft_lstadd_back(&(t->tokens), ft_lstnew(token));
	else
		t->tokens = ft_lstnew(token);
	t->remove_char(t, s, ty);
}

static void	tokenizer_finish(t_tokenizer *t)
{
	t_token	*token;

	if (t->token_type != T_T_NONE)
	{
		token = token_constructor(t->token_type, &(t->line[t->start_cursor]));
		if (t->tokens)
			ft_lstadd_back(&(t->tokens), ft_lstnew(token));
		else
			t->tokens = ft_lstnew(token);
		while (t->line[t->end_cursor] && !is_whitespace(t->line[t->end_cursor]))
			t->end_cursor++;
		t->line[t->end_cursor] = '\0';
	}
	t->state = S_T_FINISHED;
}

static void	tokens_free(t_tokenizer *t)
{
	t_list	*tmp;

	while (t->tokens)
	{
		tmp = t->tokens->next;
		((t_token *)(t->tokens->content))->free((t_token *)(t->tokens->content));
		t->tokens = tmp;
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

t_tokenizer	*tokenizer_constructor(char *line)
{
	t_tokenizer	*tokens;

	tokens = malloc(sizeof(t_tokenizer));
	*tokens = (t_tokenizer)
	{
		.list = NULL,
		line,
		.start_cursor = 0,
		.end_cursor = 0,
		.token_type = T_T_NONE,
		.state = S_T_NOT_TOKEN,
		.event = 0,
		.append_char = tokens_append_char,
		.new_token = tokens_new_token,
		.remove_char = tokens_remove_char,
		.delimit_token = tokens_delimit_token,
	};
	return (tokens);
}

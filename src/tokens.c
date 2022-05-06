/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:33:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/06 10:56:33 by seb              ###   ########.fr       */
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
	t->start_cursor = t->cursor;
	t->cursor++;
}

static void	tokens_append_char(t_tokenizer *t, t_tokenizer_state s, t_token_type type)
{
	t->state = s;
	t->token_type = type;
	t->cursor++;
}

static void	tokens_remove_char(t_tokenizer *t, t_tokenizer_state s, t_token_type type)
{
	t->line[t->cursor] = 0;
	t->state = s;
	t->token_type = type;
	t->cursor++;
	t->start_cursor = t->cursor;
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
		while (t->line[t->cursor] && !is_whitespace(t->line[t->cursor]))
			t->cursor++;
		t->line[t->cursor] = '\0';
	}
	t->state = S_T_FINISHED;
}

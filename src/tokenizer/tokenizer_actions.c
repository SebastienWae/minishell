/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:45:59 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 11:20:52 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <libft.h>
#include <utils.h>
#include <tokenizer.h>

void	tokenizer_new_token(t_tokenizer *t, t_token_type type)
{
	t_token	*token;

	token = token_constructor(type, &(t->line[t->cursor]));
	if (!token)
	{
		t->state = T_S_ERROR;
		return ;
	}
	t->curr_token = token;
	t->cursor++;
}

void	tokenizer_delimit_curr_token(t_tokenizer *t)
{
	t_list	*new;

	if (t->curr_token)
	{
		if (t->curr_token->str)
			t->curr_token->str = ft_strdup(t->curr_token->str);
		new = ft_lstnew(t->curr_token);
		if (!new)
		{
			t->state = T_S_ERROR;
			return ;
		}
		if (t->tokens)
			ft_lstadd_back(&(t->tokens), new);
		else
			t->tokens = new;
	}
	t->curr_token = NULL;
}

void	tokenizer_delimit_new(t_tokenizer *t, t_token_type type)
{
	tokenizer_delimit_curr_token(t);
	if (t->state == T_S_WORKING)
		tokenizer_new_token(t, type);
}

void	tokenizer_increase_cursor(t_tokenizer *t, t_token_type type)
{
	t->curr_token->type = type;
	t->cursor++;
}

void	tokenizer_error_token(t_tokenizer *t, t_token_type type)
{
	char	*whitespace;

	whitespace = ft_strrchr(&(t->line[t->cursor]), ' ');
	if (!whitespace)
		whitespace = ft_strrchr(&(t->line[t->cursor]), '\t');
	if (whitespace)
		t->line[whitespace - t->line] = 0;
	if (t->curr_token)
		tokenizer_delimit_curr_token(t);
	tokenizer_new_token(t, type);
	tokenizer_delimit_curr_token(t);
	t->state = T_S_FINISHED;
}

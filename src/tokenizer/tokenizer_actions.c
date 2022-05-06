/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:45:59 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 17:03:56 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <libft.h>

void	tokenizer_new_token(t_tokenizer *t, t_token_type type)
{
	t_token	*token;

	token = token_constructor(type, &(t->line[t->cursor]));
	t->curr_token = token;
	t->cursor++;
}

void	tokenizer_delimit_curr_token(t_tokenizer *t)
{
	if (t->tokens)
		ft_lstadd_back(&(t->tokens), ft_lstnew(t->curr_token));
	else
		t->tokens = ft_lstnew(t->curr_token);
	t->curr_token = NULL;
}

void	tokenizer_delimit_new(t_tokenizer *t, t_token_type type)
{
	tokenizer_delimit_curr_token(t);
	tokenizer_new_token(t, type);
}

void	tokenizer_increase_cursor(t_tokenizer *t, t_token_type type)
{
	t->curr_token->type = type;
	t->cursor++;
}

void	tokenizer_error_token(t_tokenizer *t, t_token_type type)
{
	char	*str;

	str = ft_substr(t->line, t->cursor,
			ft_strrchr(&(t->line[t->cursor]), ' ') - t->line);
	if (t->curr_token)
		tokenizer_delimit_curr_token(t);
	t->line[t->cursor] = 0;
	tokenizer_new_token(t, type);
	t->curr_token->str = str;
	tokenizer_delimit_curr_token(t);
	t->state = T_S_FINISHED;
}

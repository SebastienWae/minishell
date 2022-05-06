/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:45:59 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 11:57:52 by seb              ###   ########.fr       */
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
}

void	tokenizer_delimit_and_new(t_tokenizer *t, t_token_type type)
{
	tokenizer_delimit_curr_token(t);
	tokenizer_new_token(t, type);
}

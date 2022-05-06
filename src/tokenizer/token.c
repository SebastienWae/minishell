/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:22:40 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 17:04:22 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <stdlib.h>

static void	token_free(t_token *token)
{
	if (token->type == T_TT_UNIMPLEMENTED
		|| token->type == T_TT_SYNTAX_ERROR)
		free(token->str);
	*token = (t_token)
	{
		.str = NULL,
		.type = 0,
		.free = NULL
	};
	free(token);
}

t_token	*token_constructor(t_token_type type, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	*token = (t_token)
	{
		str,
		type,
		.free = token_free
	};
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:22:40 by seb               #+#    #+#             */
/*   Updated: 2022/05/04 21:54:46 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <stdlib.h>

static void	token_free(t_token *token)
{
	free(token->token);
	*token = (t_token)
	{
		.type = 0,
		.token = NULL,
		.free = NULL
	};
	free(token);
}

t_token	token_constructor(t_token_type type, char *token)
{
	return ((t_token)
		{
			.type = type,
			.token = token,
			.free = token_free
		});
}

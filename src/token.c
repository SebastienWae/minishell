/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:22:40 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 10:31:08 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <stdlib.h>

static void	token_free(t_token *token)
{
	free(token->token);
	*token = (t_token)
	{
		.type = T_T_NONE,
		.token = NULL,
		.free = NULL
	};
	free(token);
}

t_token	token_constructor(t_token_type type, char *token)
{
	return ((t_token)
		{
			type,
			token,
			.free = token_free
		});
}

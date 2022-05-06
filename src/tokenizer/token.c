/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:22:40 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 10:27:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <stdlib.h>

static void	token_free(t_token **token)
{
	**token = (t_token)
	{
		.str = NULL,
		.type = 0,
		.free = NULL
	};
	free(*token);
	token = NULL;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:10:49 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 16:02:28 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <expand.h>

void	expand_quote_handler(t_expand *e);

void	expand_var_handler(t_expand *e);

void	expand_space_handler(t_expand *e);

void	expand_char_handler(t_expand *e)
{
	if (e->state == E_S_IN_WORD)
	{

	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{

	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{

	}
}

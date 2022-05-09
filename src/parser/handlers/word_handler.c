/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:49:12 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/09 16:54:39 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <parser.h>

void	parser_word_handler(t_parser *p, t_token *t)
{
	static	t_parser_token_handlers	handlers[] = {

	};

	if (p->curr_cmd)
		return ;
	else
		return ;
}

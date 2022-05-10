/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:48 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 17:23:22 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>

// TODO: fix me
void	parser_syntax_error(t_parser *p, t_token *t)
{
	printf("Syntax error: %s\n", t->str);
	p->state = P_S_ERROR;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:47:01 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 14:48:00 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <tokenizer.h>

void	parser_new_redir(t_parser *p)
{
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

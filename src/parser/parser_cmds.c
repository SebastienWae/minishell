/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/09 18:32:23 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_add_to_cmd(t_parser *p, t_token *t);
void	parser_new_cmd(t_parser *p, t_token *t);

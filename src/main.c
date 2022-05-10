/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:18 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 17:24:17 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <tokenizer.h>
#include <minishell.h>
#include <debug.h>

int	main(int argc, char **argv)
{
	t_tokenizer	*t;
	t_parser	*p;

	if (argc == 2)
	{
		t = tokenize(argv[1]);
		print_tokenizer(t);
		p = parse(t);
		print_parser(p);
		t->destructor(t);
		p->destructor(p);
	}
	return (0);
}

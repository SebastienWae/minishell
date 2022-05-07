/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:18 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/07 14:00:21 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <minishell.h>
#include <debug.h>

int	main(int argc, char **argv)
{
	t_tokenizer	*t;

	if (argc == 2)
	{
		t = tokenizer(argv[1]);
		print_tokenizer(t);
		t->free(t);
	}
	return (0);
}

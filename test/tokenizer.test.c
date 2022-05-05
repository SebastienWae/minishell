/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:24:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 13:21:24 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <tokenizer.h>

static void	tokenizer_simple(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "echo 123";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "123");
	assert_null(list->next);
	tokens->free(tokens);
}

int	main(void)
{
	const struct CMUnitTest	tokenizer_tests[] = {
		cmocka_unit_test(tokenizer_simple),
	};

	return (cmocka_run_group_tests(tokenizer_tests, NULL, NULL));
}
#define FD_LIMIT

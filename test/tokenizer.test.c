/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:24:56 by seb               #+#    #+#             */
/*   Updated: 2022/04/29 11:49:28 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <minishell.h>

static void	tokenizer_simple(void **state)
{
	t_list	*head;
	t_list	*tokens;
	char	line[] = "echo 123";

	(void)state;
	tokens = tokenizer(line);
	head = tokens;
	assert_int_equal(((t_token *)tokens->content)->type, WORD);
	assert_string_equal(((t_token *)tokens->content)->data.word, "echo");
	assert_non_null(tokens->next);
	tokens = tokens->next;
	assert_int_equal(((t_token *)tokens->content)->type, WORD);
	assert_string_equal(((t_token *)tokens->content)->data.word, "123");
	assert_null(tokens->next);
	free_tokens(head);
}

static void	tokenizer_simple_extra_whitespace(void **state)
{
	t_list	*head;
	t_list	*tokens;
	char	line[] = "  \necho \t  123  \n  ";

	(void)state;
	tokens = tokenizer(line);
	head = tokens;
	assert_int_equal(((t_token *)tokens->content)->type, WORD);
	assert_string_equal(((t_token *)tokens->content)->data.word, "echo");
	assert_non_null(tokens->next);
	tokens = tokens->next;
	assert_int_equal(((t_token *)tokens->content)->type, WORD);
	assert_string_equal(((t_token *)tokens->content)->data.word, "123");
	assert_null(tokens->next);
	free_tokens(head);
}

int	main(void)
{
	const struct CMUnitTest	tokenizer_tests[] = {
		cmocka_unit_test(tokenizer_simple),
		cmocka_unit_test(tokenizer_simple_extra_whitespace),
	};

	return (cmocka_run_group_tests(tokenizer_tests, NULL, NULL));
}

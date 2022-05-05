/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:24:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 16:37:38 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <tokenizer.h>

static void	tokenizer_empty(void **state)
{
	t_tokens	*tokens;
	char		line[] = "";

	(void)state;
	tokens = tokenizer(line);
	assert_null(tokens->list);
	tokens_free(tokens);
}

static void	tokenizer_whitespaces(void **state)
{
	t_tokens	*tokens;
	char		line[] = "  \t  \t  ";

	(void)state;
	tokens = tokenizer(line);
	assert_null(tokens->list);
	tokens_free(tokens);
}

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
	tokens_free(tokens);
}

static void	tokenizer_operators(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "< in cat << EOF | cat > out | echo 123 >> out";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_REDIRECTION_IN);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "in");
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "EOF");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_REDIRECTION_OUT);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "out");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "123");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_REDIRECTION_APPEND);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "out");
	assert_null(list->next);
	tokens_free(tokens);
}

static void	tokenizer_quotes(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "echo '$h dd - ><> || <<'   |echo test\"ing\">out ";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "'$h dd - ><> || <<'");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "test\"ing\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_REDIRECTION_OUT);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "out");
	assert_null(list->next);
	tokens_free(tokens);
}

static void	tokenizer_unimplemented(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "    cat<<\"EOF\"| <<< test echo 123";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "\"EOF\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_UNIMPLEMENTED);
	assert_null(list->next);
	tokens_free(tokens);
}

static void	tokenizer_unimplemented2(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "    cat<<\"EOF\"| '&' & test echo 123";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "\"EOF\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "'&'");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_UNIMPLEMENTED);
	assert_null(list->next);
	tokens_free(tokens);
}

static void	tokenizer_syntax(void **state)
{
	t_list		*list;
	t_tokens	*tokens;
	char		line[] = "    cat<<\"EOF\"| <<> test echo 123";

	(void)state;
	tokens = tokenizer(line);
	list = tokens->list;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_WORD);
	assert_string_equal(((t_token *)list->content)->token, "\"EOF\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_T_SYNTAX_ERROR);
	assert_null(list->next);
	tokens_free(tokens);
}

int	main(void)
{
	const struct CMUnitTest	tokenizer_tests[] = {
		cmocka_unit_test(tokenizer_empty),
		cmocka_unit_test(tokenizer_whitespaces),
		cmocka_unit_test(tokenizer_simple),
		cmocka_unit_test(tokenizer_operators),
		cmocka_unit_test(tokenizer_quotes),
		cmocka_unit_test(tokenizer_unimplemented),
		cmocka_unit_test(tokenizer_unimplemented2),
		cmocka_unit_test(tokenizer_syntax),
	};

	return (cmocka_run_group_tests(tokenizer_tests, NULL, NULL));
}

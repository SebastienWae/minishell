/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:24:56 by seb               #+#    #+#             */
/*   Updated: 2022/05/18 13:30:35 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <minishell.h>
#include <tokenizer.h>

static void	tokenizer_empty(void **state)
{
	t_tokenizer	*tokens;
	char		line[] = "";

	(void)state;
	tokens = tokenize(line);
	assert_null(tokens->tokens);
	tokens->destructor(tokens);
}

static void	tokenizer_whitespaces(void **state)
{
	t_tokenizer	*tokens;
	char		line[] = "  \t  \t  ";

	(void)state;
	tokens = tokenize(line);
	assert_null(tokens->tokens);
	tokens->destructor(tokens);
}

static void	tokenizer_simple(void **state)
{
	t_list		*list;
	t_tokenizer	*tokens;
	char		line[] = "echo 123";

	(void)state;
	tokens = tokenize(line);
	list = tokens->tokens;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "123");
	assert_null(list->next);
	tokens->destructor(tokens);
}

static void	tokenizer_operators(void **state)
{
	t_list		*list;
	t_tokenizer	*tokens;
	char		line[] = "< in cat << EOF | cat > out | echo 123 >> out";

	(void)state;
	tokens = tokenize(line);
	list = tokens->tokens;
	assert_int_equal(((t_token *)list->content)->type, T_TT_REDIR_IN);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "in");
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "EOF");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_REDIR_OUT);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "out");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "123");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_REDIR_APPEND);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "out");
	assert_null(list->next);
	tokens->destructor(tokens);
}

static void	tokenizer_quotes(void **state)
{
	t_list		*list;
	t_tokenizer	*tokens;
	char		line[] = "echo '$h dd - ><> || <<'   |echo test\"ing\">out ";

	(void)state;
	tokens = tokenize(line);
	list = tokens->tokens;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "'$h dd - ><> || <<'");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "echo");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "test\"ing\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_REDIR_OUT);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "out");
	assert_null(list->next);
	tokens->destructor(tokens);
}

static void	tokenizer_syntax(void **state)
{
	t_list		*list;
	t_tokenizer	*tokens;
	char		line[] = "    cat<<\"EOF\"| <<> test echo 123";

	(void)state;
	tokens = tokenize(line);
	list = tokens->tokens;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "cat");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "\"EOF\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_SYNTAX_ERROR);
	assert_null(list->next);
	tokens->destructor(tokens);
}

static void	tokenizer_syntax2(void **state)
{
	t_list		*list;
	t_tokenizer	*tokens;
	char		line[] = "    cat& ; ; <<\"EOF\"|<|>|'te's&techo123";

	(void)state;
	tokens = tokenize(line);
	list = tokens->tokens;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "cat&");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, ";");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, ";");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_HEREDOC);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_WORD);
	assert_string_equal(((t_token *)list->content)->str, "\"EOF\"");
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_PIPE);
	assert_non_null(list->next);
	list = list->next;
	assert_int_equal(((t_token *)list->content)->type, T_TT_SYNTAX_ERROR);
	assert_null(list->next);
	tokens->destructor(tokens);
}

int	main(void)
{
	const struct CMUnitTest	tokenizer_tests[] = {
		cmocka_unit_test(tokenizer_empty),
		cmocka_unit_test(tokenizer_whitespaces),
		cmocka_unit_test(tokenizer_simple),
		cmocka_unit_test(tokenizer_operators),
		cmocka_unit_test(tokenizer_quotes),
		cmocka_unit_test(tokenizer_syntax),
		cmocka_unit_test(tokenizer_syntax2),
	};

	return (cmocka_run_group_tests(tokenizer_tests, NULL, NULL));
}

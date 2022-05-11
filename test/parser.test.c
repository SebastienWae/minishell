/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:08:38 by seb               #+#    #+#             */
/*   Updated: 2022/05/11 08:38:10 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <minishell.h>

static void	parser_empty(void **state)
{
	t_tokenizer	*tokens;
	t_parser	*parser;
	char		line[] = "";

	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens);
	assert_null(parser->cmds);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_whitespaces(void **state)
{
	t_tokenizer	*tokens;
	t_parser	*parser;
	char		line[] = "    \t    \t ";

	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens);
	assert_null(parser->cmds);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_simple(void **state)
{
	t_list		*cmd;
	t_tokenizer	*tokens;
	t_parser	*parser;
	char		line[] = "echo 123";

	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens);
	cmd = parser->cmds;
	assert_string_equal(((t_cmd *)(cmd->content))->cmd, "echo 123");
	assert_null(((t_cmd *)(cmd->content))->in);
	assert_null(((t_cmd *)(cmd->content))->out);
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 0);
	cmd = cmd->next;
	assert_null(cmd);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_redir_in(void **state)
{
	t_list		*cmd;
	t_list		*in;
	t_tokenizer	*tokens;
	t_parser	*parser;
	char		line[] = "< in echo << HERE 123 <in";

	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens);
	cmd = parser->cmds;
	in = ((t_cmd *)(cmd->content))->in;
	assert_string_equal(((t_cmd *)(cmd->content))->cmd, "echo 123");
	assert_int_equal(((t_redir *)(in->content))->type, P_RT_IN);
	assert_string_equal(((t_redir *)(in->content))->target, "in");
	assert_non_null(in->next);
	in = in->next;
	assert_int_equal(((t_redir *)(in->content))->type, P_RT_HEREDOC);
	assert_string_equal(((t_redir *)(in->content))->target, "HERE");
	assert_non_null(in->next);
	in = in->next;
	assert_int_equal(((t_redir *)(in->content))->type, P_RT_IN);
	assert_string_equal(((t_redir *)(in->content))->target, "in");
	assert_null(in->next);
	assert_null(((t_cmd *)(cmd->content))->out);
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 0);
	cmd = cmd->next;
	assert_null(cmd);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

int	main(void)
{
	const struct CMUnitTest	parser_tests[] = {
		cmocka_unit_test(parser_empty),
		cmocka_unit_test(parser_whitespaces),
		cmocka_unit_test(parser_simple),
		cmocka_unit_test(parser_redir_in),
	};

	return (cmocka_run_group_tests(parser_tests, NULL, NULL));
}

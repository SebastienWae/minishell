/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:08:38 by seb               #+#    #+#             */
/*   Updated: 2022/05/16 16:16:45 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <minishell.h>
#include <parser.h>

int	g_out;

static t_minishell	*shell_builder(int n, ...)
{
	va_list		ap;
	t_minishell	*shell;
	t_list		*env;
	char		*el;

	va_start(ap, n);
	env = NULL;
	while (n)
	{
		el = va_arg(ap, char *);
		if (env)
			ft_lstadd_back(&env, ft_lstnew(el));
		else
			env = ft_lstnew(el);
		n--;
	}
	shell = malloc(sizeof(t_minishell));
	*shell = (t_minishell)
	{
		.local_env = env,
		.config = {0},
		.saved_stdin = 0,
		.saved_stdout = 0
	};
	return (shell);
}

static void	parser_empty(void **state)
{
	t_tokenizer	*tokens;
	t_parser	*parser;
	t_minishell	*shell;
	char		line[] = "";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
	assert_null(parser->cmds);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_whitespaces(void **state)
{
	t_tokenizer	*tokens;
	t_parser	*parser;
	t_minishell	*shell;
	char		line[] = "    \t    \t ";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
	assert_null(parser->cmds);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_simple(void **state)
{
	t_list		*cmd;
	t_tokenizer	*tokens;
	t_parser	*parser;
	t_minishell	*shell;
	char		line[] = "echo 123";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
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
	t_minishell	*shell;
	char		line[] = "< in echo << HERE 123 <in";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
	cmd = parser->cmds;
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 0);
	assert_null(((t_cmd *)(cmd->content))->out);
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
	cmd = cmd->next;
	assert_null(cmd);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_redir_out(void **state)
{
	t_list		*cmd;
	t_list		*out;
	t_tokenizer	*tokens;
	t_parser	*parser;
	t_minishell	*shell;
	char		line[] = "> out echo >>append 123 >out";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
	cmd = parser->cmds;
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 0);
	assert_null(((t_cmd *)(cmd->content))->in);
	out = ((t_cmd *)(cmd->content))->out;
	assert_string_equal(((t_cmd *)(cmd->content))->cmd, "echo 123");
	assert_int_equal(((t_redir *)(out->content))->type, P_RT_OUT);
	assert_string_equal(((t_redir *)(out->content))->target, "out");
	assert_non_null(out->next);
	out = out->next;
	assert_int_equal(((t_redir *)(out->content))->type, P_RT_APPEND);
	assert_string_equal(((t_redir *)(out->content))->target, "append");
	assert_non_null(out->next);
	out = out->next;
	assert_int_equal(((t_redir *)(out->content))->type, P_RT_OUT);
	assert_string_equal(((t_redir *)(out->content))->target, "out");
	assert_null(out->next);
	cmd = cmd->next;
	assert_null(cmd);
	tokens->destructor(tokens);
	parser->destructor(parser);
}

static void	parser_redir_pipe(void **state)
{
	t_list		*cmd;
	t_list		*in;
	t_list		*out;
	t_tokenizer	*tokens;
	t_parser	*parser;
	t_minishell	*shell;
	char		line[] = "echo 123 | cat < in > out";

	shell = shell_builder(0, NULL);
	(void)state;
	tokens = tokenize(line);
	parser = parse(tokens, shell);
	cmd = parser->cmds;
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 1);
	assert_null(((t_cmd *)(cmd->content))->in);
	assert_null(((t_cmd *)(cmd->content))->out);
	assert_string_equal(((t_cmd *)(cmd->content))->cmd, "echo 123");
	cmd = cmd->next;
	assert_non_null(cmd);
	assert_int_equal(((t_cmd *)(cmd->content))->piped, 0);
	in = ((t_cmd *)(cmd->content))->in;
	out = ((t_cmd *)(cmd->content))->out;
	assert_string_equal(((t_cmd *)(cmd->content))->cmd, "cat");
	assert_int_equal(((t_redir *)(in->content))->type, P_RT_IN);
	assert_string_equal(((t_redir *)(in->content))->target, "in");
	assert_null(in->next);
	assert_int_equal(((t_redir *)(out->content))->type, P_RT_OUT);
	assert_string_equal(((t_redir *)(out->content))->target, "out");
	assert_null(out->next);
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
		cmocka_unit_test(parser_redir_out),
		cmocka_unit_test(parser_redir_pipe),
	};
	return (cmocka_run_group_tests(parser_tests, NULL, NULL));
}

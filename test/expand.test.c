/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:52:03 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 15:42:51 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <limits.h>

#include <minishell.h>
#include <expand.h>
#include <utils.h>

int		g_out;

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

static void	expand_empty(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(0, NULL);
	expanded = expand("", 0, shell);
	assert_null(expanded->result);
	expanded->destroy(expanded);
}

static void	expand_nothing(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(0, NULL);
	expanded = expand("echo 123", 0, shell);
	assert_string_equal(expanded->result, "echo 123");
	expanded->destroy(expanded);
}

static void	expand_unquote_flag_ok(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(0, NULL);
	expanded = expand("echo 'test' \"test\"", E_UNQUOTE, shell);
	assert_string_equal(expanded->result, "echo test test");
	expanded->destroy(expanded);
}

static void	expand_unquote_flag_no(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(0, NULL);
	expanded = expand("echo 'test' \"test\"", 0, shell);
	assert_string_equal(expanded->result, "echo 'test' \"test\"");
	expanded->destroy(expanded);
}

static void	expand_var_flag_ok(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo $USER", E_VARIABLE, shell);
	assert_string_equal(expanded->result, "echo swaegene");
	expanded->destroy(expanded);
}

static void	expand_var_flag_no(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo $USER", 0, shell);
	assert_string_equal(expanded->result, "echo $USER");
	expanded->destroy(expanded);
}

static void	expand_var_quotes_flags_ok(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo ' $USER ' \"$USER\"", E_VARIABLE | E_UNQUOTE, shell);
	assert_string_equal(expanded->result, "echo  $USER  swaegene");
	expanded->destroy(expanded);
}

static void	expand_var_quotes_flags_unquote(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo ' $USER ' \" $USER \"", E_UNQUOTE, shell);
	assert_string_equal(expanded->result, "echo  $USER   $USER ");
	expanded->destroy(expanded);
}

static void	expand_var_quotes_flags_variable(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo ' $USER ' \" $USER \"", E_VARIABLE, shell);
	assert_string_equal(expanded->result, "echo ' $USER ' \" swaegene \"");
	expanded->destroy(expanded);
}

static void	expand_var_quotes_flags_no(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo ' $USER ' \" $USER \"", 0, shell);
	assert_string_equal(expanded->result, "echo ' $USER ' \" $USER \"");
	expanded->destroy(expanded);
}

static void	expand_question(void **state)
{
	t_expand	*expanded;
	t_minishell	*shell;

	(void)state;
	g_out = 123;
	shell = shell_builder(1, "USER=swaegene");
	expanded = expand("echo ' $? ' $?", E_VARIABLE, shell);
	assert_string_equal(expanded->result, "echo ' $? ' 123");
	expanded->destroy(expanded);
}

int	main(void)
{
	const struct CMUnitTest	expand_test[] = {
		cmocka_unit_test(expand_empty),
		cmocka_unit_test(expand_nothing),
		cmocka_unit_test(expand_unquote_flag_ok),
		cmocka_unit_test(expand_unquote_flag_no),
		cmocka_unit_test(expand_var_flag_ok),
		cmocka_unit_test(expand_var_flag_no),
		cmocka_unit_test(expand_var_quotes_flags_ok),
		cmocka_unit_test(expand_var_quotes_flags_unquote),
		cmocka_unit_test(expand_var_quotes_flags_variable),
		cmocka_unit_test(expand_var_quotes_flags_no),
		cmocka_unit_test(expand_question),
	};

	return (cmocka_run_group_tests(expand_test, NULL, NULL));
}

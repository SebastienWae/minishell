/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:08:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 13:23:44 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <minishell.h>
#include <stdlib.h>
#include <utils.h>

t_variable	*variable_constructor(int start)
{
	t_variable	*variable;

	variable = malloc(sizeof(t_variable));
	if (!variable)
		return (NULL);
	*variable = (t_variable){start, 0};
	return (variable);
}

static void	expand_destructor(t_expand *self)
{
	if (self->variable)
		free(self->variable);
	*self = (t_expand){
		.str = NULL,
		.flags = 0,
		.shell = NULL,
		.result = NULL,
		.cursor = 0,
		.variable = NULL,
		.state = 0,
		.destroy = NULL};
	free(self);
}

static t_expand	*expand_constructor(char *str, int flags, t_minishell *shell)
{
	t_expand	*self;

	self = malloc(sizeof(t_expand));
	if (!self)
		return (NULL);
	*self = (t_expand){
		str,
		flags,
		shell,
		.result = NULL,
		.cursor = 0,
		.variable = NULL,
		.state = E_S_EXPANDING,
		.destroy = expand_destructor};
	return (self);
}

t_expand	*expand(char *str, t_expand_flag flags, t_minishell *shell)
{
	t_expand	*expand;

	expand = expand_constructor(str, flags, shell);
	if (!expand)
		return (NULL);
	while (expand->state != E_S_FINISHED)
	{
		if (!expand->str[expand->cursor])
			expand_finish(expand);
		else if (expand->str[expand->cursor] == '\'')
			expand_single_quote_handler(expand);
		else if (expand->str[expand->cursor] == '"')
			expand_double_quote_handler(expand);
		else if (expand->str[expand->cursor] == '$')
			expand_var_handler(expand);
		else if (is_whitespace(expand->str[expand->cursor]))
			expand_space_handler(expand);
		else
			expand_char_handler(expand);
		expand->cursor++;
	}
	return (expand);
}

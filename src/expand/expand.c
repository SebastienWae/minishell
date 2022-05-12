/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:08:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 17:31:04 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <utils.h>
#include <expand.h>

t_variable	*variable_constructor(int start, int end)
{
	t_variable	*variable;

	variable = malloc(sizeof(t_variable));
	if (!variable)
		return (NULL);
	*variable = (t_variable){start, end};
	return (variable);
}

static void	expand_destructor(t_expand *self)
{
	free(self->str);
	if (self->variable)
		free(self->variable);
	*self = (t_expand)
	{
		.str = NULL,
		.flags = 0,
		.result = NULL,
		.cursor = 0,
		.variable = NULL,
		.state = 0,
		.destructor = NULL
	};
	free(self);
}

static t_expand	*expand_constructor(char *str, int flags)
{
	t_expand		*self;

	self = malloc(sizeof(t_expand));
	if (!self)
		return (NULL);
	*self = (t_expand)
	{
		str,
		flags,
		.result = NULL,
		.cursor = 0,
		.variable = NULL,
		.state = E_S_EXPANDING,
		.destructor = expand_destructor
	};
	return (self);
}

t_expand	*expand(char *str, int flags)
{
	t_expand	*expand;

	expand = expand_constructor(str, flags);
	while (expand->state != E_S_FINISHED)
	{
		if (!expand->str[expand->cursor])
			expand->state = E_S_FINISHED;
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
	}
	return (expand);
}

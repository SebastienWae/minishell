/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:10:49 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/18 11:06:19 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <stdlib.h>

void	expand_var_handler(t_expand *e)
{
	if (e->state == E_S_EXPANDING || e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if ((e->flags & E_VARIABLE) > 0 || (e->flags & E_FORCE_VARIABLE) > 0)
		{
			if (e->variable)
				expand_append_var(e);
			e->variable = variable_constructor(e->cursor + 1);
		}
		else
			expand_append_char(e);
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_FORCE_VARIABLE) > 0)
		{
			if (e->variable)
				expand_append_var(e);
			e->variable = variable_constructor(e->cursor + 1);
		}
		else
			expand_append_char(e);
	}
	e->cursor++;
}

void	expand_single_quote_handler(t_expand *e)
{
	if (e->state == E_S_EXPANDING)
	{
		if (e->variable)
			expand_var_handler(e);
		if ((e->flags & E_UNQUOTE) == 0)
			expand_append_char(e);
		e->state = E_S_IN_SINGLE_QUOTE;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_FORCE_VARIABLE) > 0 && e->variable)
			expand_append_var(e);
		if ((e->flags & E_UNQUOTE) == 0)
			expand_append_char(e);
		else if (!e->result)
		{
			// fix derefence
			e->result = malloc(sizeof(char));
			e->result[0] = 0;
		}
		e->state = E_S_EXPANDING;
	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
			expand_append_var(e);
		expand_append_char(e);
	}
	e->cursor++;
}

void	expand_double_quote_handler(t_expand *e)
{
	if (e->state == E_S_EXPANDING)
	{
		if (e->variable)
			expand_append_var(e);
		if ((e->flags & E_UNQUOTE) == 0)
			expand_append_char(e);
		e->state = E_S_IN_DOUBLE_QUOTE;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_FORCE_VARIABLE) > 0 && e->variable)
			expand_append_var(e);
		else
			expand_append_char(e);
	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
			expand_append_var(e);
		if ((e->flags & E_UNQUOTE) == 0)
			expand_append_char(e);
		else if (!e->result)
		{
			// fix derefence
			e->result = malloc(sizeof(char));
			e->result[0] = 0;
		}
		e->state = E_S_EXPANDING;
	}
	e->cursor++;
}

void	expand_space_handler(t_expand *e)
{
	if (e->state == E_S_EXPANDING || e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
			expand_append_var(e);
		expand_append_char(e);
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_FORCE_VARIABLE) > 0 && e->variable)
			expand_append_var(e);
		expand_append_char(e);
	}
	else
		e->state = E_S_ERROR;
	e->cursor++;
}

void	expand_char_handler(t_expand *e)
{
	if (e->state == E_S_EXPANDING || e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
			e->variable->end++;
		else
			expand_append_char(e);
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_FORCE_VARIABLE) > 0 && e->variable)
			e->variable->end++;
		else
			expand_append_char(e);
	}
	else
		e->state = E_S_ERROR;
	e->cursor++;
}

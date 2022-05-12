/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:10:49 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 17:38:06 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <libft.h>
#include <stdlib.h>
#include <utils.h>

void	expand_var_handler(t_expand *e)
{
	char	*tmp;
	char	*var;

	if (e->state == E_S_EXPANDING)
	{
		if ((e->flags & E_VARIABLE) > 0)
		{
			if (e->variable)
			{
				var = ft_substr(e->str, e->variable->start, e->variable->end);
				tmp = e->result;
				e->result = ft_strjoin(e->result, var);
				free(tmp);
				free(e->variable);
				e->variable = NULL;
			}
			e->variable = variable_constructor(e->cursor + 1, e->cursor + 1);
		}
		else
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		tmp = e->result;
		e->result = ft_strappend(e->result, e->str[e->cursor]);
		free(tmp);
		e->cursor++;
	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if ((e->flags & E_VARIABLE) > 0)
		{
			if (e->variable)
			{
				var = ft_substr(e->str, e->variable->start, e->variable->end);
				tmp = e->result;
				e->result = ft_strjoin(e->result, var);
				free(tmp);
				free(e->variable);
				e->variable = NULL;
			}
			e->variable = variable_constructor(e->cursor + 1, e->cursor + 1);
		}
		else
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
	}
}

void	expand_single_quote_handler(t_expand *e)
{
	char	*tmp;
	char	*var;

	if (e->state == E_S_EXPANDING)
	{
		if (e->variable)
		{
			var = ft_substr(e->str, e->variable->start, e->variable->end);
			tmp = e->result;
			e->result = ft_strjoin(e->result, var);
			free(tmp);
			free(e->variable);
			e->variable = NULL;
		}
		if ((e->flags & E_UNQUOTE) == 0)
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
		e->state = E_S_IN_DOUBLE_QUOTE;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		if ((e->flags & E_UNQUOTE) == 0)
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
		e->state = E_S_EXPANDING;
	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{
		tmp = e->result;
		e->result = ft_strappend(e->result, e->str[e->cursor]);
		free(tmp);
		e->cursor++;
	}
}

void	expand_double_quote_handler(t_expand *e)
{
	char	*tmp;
	char	*var;

	if (e->state == E_S_EXPANDING)
	{
		if (e->variable)
		{
			var = ft_substr(e->str, e->variable->start, e->variable->end);
			tmp = e->result;
			e->result = ft_strjoin(e->result, var);
			free(tmp);
			free(e->variable);
			e->variable = NULL;
		}
		if ((e->flags & E_UNQUOTE) == 0)
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
		e->state = E_S_IN_DOUBLE_QUOTE;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
	{
		tmp = e->result;
		e->result = ft_strappend(e->result, e->str[e->cursor]);
		free(tmp);
		e->cursor++;
	}
	else if (e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
		{
			var = ft_substr(e->str, e->variable->start, e->variable->end);
			tmp = e->result;
			e->result = ft_strjoin(e->result, var);
			free(tmp);
			free(e->variable);
			e->variable = NULL;
		}
		if ((e->flags & E_UNQUOTE) == 0)
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
		e->state = E_S_EXPANDING;
	}
}

void	expand_space_handler(t_expand *e)
{
	char	*tmp;
	char	*var;

	if (e->state == E_S_EXPANDING || e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
		{
			var = ft_substr(e->str, e->variable->start, e->variable->end);
			tmp = e->result;
			e->result = ft_strjoin(e->result, var);
			free(tmp);
			free(e->variable);
			e->variable = NULL;
		}
		tmp = e->result;
		e->result = ft_strappend(e->result, e->str[e->cursor]);
		free(tmp);
		e->cursor++;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
		e->cursor++;
	else
		e->state = E_S_ERROR;
}

void	expand_char_handler(t_expand *e)
{
	char	*tmp;

	if (e->state == E_S_EXPANDING || e->state == E_S_IN_DOUBLE_QUOTE)
	{
		if (e->variable)
			e->variable->end++;
		else
		{
			tmp = e->result;
			e->result = ft_strappend(e->result, e->str[e->cursor]);
			free(tmp);
		}
		e->cursor++;
	}
	else if (e->state == E_S_IN_SINGLE_QUOTE)
		e->cursor++;
	else
		e->state = E_S_ERROR;
}

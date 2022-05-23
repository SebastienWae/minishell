/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:31:54 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 11:46:52 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <expand.h>
#include <functions.h>
#include <stdlib.h>

void	expand_finish(t_expand *e)
{
	if (e->variable && e->state == E_S_EXPANDING)
		expand_append_var(e);
	e->state = E_S_FINISHED;
}

void	expand_add_empty(t_expand *e)
{
	e->result = malloc(sizeof(char));
	if (e->result)
		e->result[0] = 0;
	else
		e->state = E_S_ERROR;
}

void	expand_append_char(t_expand *e)
{
	char	*tmp;

	tmp = e->result;
	if (e->state != E_S_IN_DOUBLE_QUOTE && e->state != E_S_IN_SINGLE_QUOTE
		&& e->flags != E_FORCE_VAR && e->str[e->cursor] == '*')
		e->result = ft_strappend(e->result, -1);
	else
		e->result = ft_strappend(e->result, e->str[e->cursor]);
	free(tmp);
}

static char	*expand_get_var_value(t_expand *e)
{
	char	*val;
	char	*tmp;

	if (e->variable->end == 0)
	{
		if ((e->state != E_S_IN_DOUBLE_QUOTE && e->state != E_S_IN_SINGLE_QUOTE)
			&& (e->str[e->cursor] == '\'' || e->str[e->cursor] == '"'))
			val = ft_strdup("");
		else
			val = ft_strdup("$");
	}
	else if (e->variable->end == 1 && e->str[e->variable->start] == '?')
		val = ft_itoa(g_out);
	else
	{
		tmp = ft_substr(e->str, e->variable->start, e->variable->end);
		if (tmp)
		{
			val = ft_get_env_var_value(e->shell->local_env, tmp);
			free(tmp);
		}
		else
			val = NULL;
	}
	return (val);
}

void	expand_append_var(t_expand *e)
{
	char	*val;
	char	*tmp;

	val = expand_get_var_value(e);
	if (val)
	{
		if (e->state != E_S_IN_DOUBLE_QUOTE && e->state != E_S_IN_SINGLE_QUOTE
			&& e->flags != E_FORCE_VAR)
			expand_replace_wildcard(val);
		if (e->result)
		{
			tmp = e->result;
			e->result = ft_strjoin(e->result, val);
			free(tmp);
			free(val);
		}
		else
			e->result = val;
	}
	free(e->variable);
	e->variable = NULL;
}

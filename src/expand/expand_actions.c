/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:31:54 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 13:36:14 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <functions.h>
#include <stdlib.h>
#include <utils.h>

void	expand_append_char(t_expand *e)
{
	char	*tmp;

	tmp = e->result;
	e->result = ft_strappend(e->result, e->str[e->cursor]);
	free(tmp);
}

void	expand_append_var(t_expand *e)
{
	char	*tmp[2];

	if (e->variable->end == 0)
		tmp[0] = NULL;
	else if (e->variable->end == 1 && e->str[e->variable->start] == '?')
		tmp[0] = ft_itoa(g_out);
	else
	{
		tmp[1] = ft_substr(e->str, e->variable->start, e->variable->end);
		if (tmp[1])
		{
			tmp[0] = ft_get_env_var_value(e->shell->local_env, tmp[1]);
			free(tmp[1]);
		}
		else
			tmp[0] = NULL;
	}
	if (tmp[0])
	{
		tmp[1] = e->result;
		e->result = ft_strjoin(e->result, tmp[0]);
		free(tmp[1]);
	}
	free(e->variable);
	e->variable = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:48:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 11:58:42 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

void	expand_replace_wildcard(char *str)
{
	int	i;	

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			str[i] = -1;
		i++;
	}
}

void	expand_var(t_expand *e)
{
	if (e->variable->end == 0)
	{
		if (e->str[e->cursor] == '?')
		{
			e->variable->end++;
			expand_append_var(e);
		}
		else if (e->str[e->cursor] != '_' && !ft_isalpha(e->str[e->cursor]))
		{
			expand_append_var(e);
			expand_append_char(e);
		}
		else
			e->variable->end++;
	}
	else
	{
		if (!ft_isalnum(e->str[e->cursor]) && e->str[e->cursor] != '_')
		{
			expand_append_var(e);
			expand_append_char(e);
		}
		else
			e->variable->end++;
	}
}

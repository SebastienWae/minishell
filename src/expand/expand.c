/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:08:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 14:27:58 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <expand.h>

t_expand_state	expand_quote_handler(char *str, int cursor, t_expand_state s)
{
	static t_expand_handlers	handlers[] = {
	{E_S_IN_WORD, 0},
	{E_S_IN_SINGLE_QUOTE, 0},
	{E_S_IN_DOUBLE_QUOTE, 0},
	{E_S_IN_VAR, 0},
	};

	return (handlers[s - 1].handler(str, cursor));
}

t_expand_state	expand_var_handler(char *str, int cursor, t_expand_state s)
{
	static t_expand_handlers	handlers[] = {
	{E_S_IN_WORD, 0},
	{E_S_IN_SINGLE_QUOTE, 0},
	{E_S_IN_DOUBLE_QUOTE, 0},
	{E_S_IN_VAR, 0},
	};

	return (handlers[s - 1].handler(str, cursor));
}

t_expand_state	expand_space_handler(char *str, int cursor, t_expand_state s)
{
	static t_expand_handlers	handlers[] = {
	{E_S_IN_WORD, 0},
	{E_S_IN_SINGLE_QUOTE, 0},
	{E_S_IN_DOUBLE_QUOTE, 0},
	{E_S_IN_VAR, 0},
	};

	return (handlers[s - 1].handler(str, cursor));
}

t_expand_state	expand_char_handler(char *str, int cursor, t_expand_state s)
{
	static t_expand_handlers	handlers[] = {
	{E_S_IN_WORD, 0},
	{E_S_IN_SINGLE_QUOTE, 0},
	{E_S_IN_DOUBLE_QUOTE, 0},
	{E_S_IN_VAR, 0},
	};

	return (handlers[s - 1].handler(str, cursor));
}

char	*expand(char *str)
{
	int				cursor;
	t_expand_state	state;

	cursor = 0;
	state = E_S_IN_WORD;
	while (state != E_S_FINISHED)
	{
		if (!str[cursor])
			state = E_S_FINISHED;
		else if (str[cursor] == '\'' || str[cursor] == '"')
			state = expand_quote_handler(str, cursor, state);
		else if (str[cursor] == '$')
			state = expand_var_handler(str, cursor, state);
		else if (is_whitespace(str[cursor]))
			state = expand_space_handler(str, cursor, state);
		else
			state = expand_char_handler(str, cursor, state);
	}
	return (str);
}

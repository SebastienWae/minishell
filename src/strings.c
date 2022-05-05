/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/05 09:06:23 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if the character is considered to be a whitespace.
Returns 1 if true, 0 if false */
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_unimplemented(char c)
{
	if (c == '&' || c == ';' || c == '(' || c == ')' || c == '`' || c == '\\'
		|| c == '*' || c == '?' || c == '[' || c == '#' || c == '~'
		|| c == '=' || c == '%')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/04 17:46:46 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if the character is considered to be a whitespace.
Returns 1 if true, 0 if false */
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
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

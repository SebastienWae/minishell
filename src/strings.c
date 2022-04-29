/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/04/29 10:13:12 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if the character is considered to be a metacharacter.
Returns 1 if true, 0 if false */
int	is_metacharacter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/* Checks if the character is considered to be a whitespace.
Returns 1 if true, 0 if false */
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

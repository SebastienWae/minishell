/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:45:55 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 13:40:48 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function: ft_isascii
 * --------------------
 * Tests for any character between 0 and octal 0177 inclusive.
 *
 * c: the character to test
 *
 * Return: Zero if the character tests false and non-zero is the character
 * tests true.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

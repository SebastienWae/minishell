/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:47:30 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 13:39:23 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function: ft_isalpha
 * --------------------
 * Tests for any character for any lower-case or upper-case letter.
 *
 * c: the character to test
 *
 * Return: Zero if the character tests false and non-zero is the character
 * tests true.
 */
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

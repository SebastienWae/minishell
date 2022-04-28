/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:05:39 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 13:43:01 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function: ft_isdigit
 * --------------------
 * Tests for any decimal digit character.
 *
 * c: the character to test
 *
 * Return: Zero if the character tests false and non-zero is the character
 * tests true.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

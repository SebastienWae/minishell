/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:51:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 13:42:53 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function: ft_isdigit
 * --------------------
 * Tests for any printing character, including space.
 *
 * c: the character to test
 *
 * Return: Zero if the character tests false and non-zero is the character
 * tests true.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

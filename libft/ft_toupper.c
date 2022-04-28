/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:42:31 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 15:12:26 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Function: ft_toupper
 * --------------------
 * Converts an lower-case letter to the corresponding upper-case letter.
 *
 * c: the char to convert
 * 
 * Return: If the char is an lower-case, it returns the corresponding
 * upper-case, otherwise it return the char unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:51:01 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/27 15:11:53 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Function: ft_tolower
 * --------------------
 * Converts an upper-case letter to the corresponding lower-case letter.
 *
 * c: the char to convert
 * 
 * Return: If the char is an upper-case, it returns the corresponding
 * lower-case, otherwise it return the char unchanged.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

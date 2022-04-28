/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:17:02 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_bzero
 * --------------------
 * Writes n zeroed bytes to the string s.
 * Does nothing if n is zero.
 *
 * s: the string to write in.
 * n: the number of bytes to writes.
 */
void	ft_bzero(void *s, size_t n)
{
	while (n--)
		((char *)s)[n] = 0;
}

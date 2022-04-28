/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:15:45 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/15 15:13:08 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_memcpy
 * --------------------
 * Copies n bytes from memory area src to memory area dst.
 * If dst and src overlap, behavior is undefined.
 *
 * dst: destination memory area.
 * src: sorce memory area.
 * n: number of bytes to copy.
 * 
 * Return: The original value of dst.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		i++;
	}
	return (dst);
}

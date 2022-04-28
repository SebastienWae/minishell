/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:05:24 by swaegene          #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_strlcat
 * --------------------
 * Appends string src to the end of dst.
 * It will append at most * dstsize - strlen(dst) - 1 characters.
 * It will then NUL-terminate, unless dstsize is 0 or the original dst string
 * was longer than dstsize (in practice this should not happen as it means
 * that either dstsize is incorrect or that dst is not a proper string).
 * 
 * dst: destination string.
 * src: source string.
 * dstsize: size to calculate the number of char to copy into dst
 * 
 * Return: The initial length of dst plus the length of src.
 * If the return value is >= dstsize, the output string has been truncated.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	result;

	i = 0;
	dst_len = ft_strlen(dst);
	result = ft_strlen(src);
	if (dst_len < dstsize)
		result += dst_len;
	else
		result += dstsize;
	if (dstsize && dstsize > dst_len)
	{
		while (i < (dstsize - dst_len - 1) && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = 0;
	}
	return (result);
}

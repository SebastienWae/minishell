/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:27:08 by seb               #+#    #+#             */
/*   Updated: 2022/02/28 12:22:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function: ft_putstr_fd
 * --------------------
 * Outputs the string ’s’ to the given file descriptor.
 *
 * s: The string to output.
 * fd: The file descriptor on which to write.
 */
void	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		ft_putchar_fd(*s++, fd);
}

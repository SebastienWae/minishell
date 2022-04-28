/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:30:48 by seb               #+#    #+#             */
/*   Updated: 2022/02/27 14:41:02 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Function: ft_striteri
 * --------------------
 * Applies the function ’f’ on each character of the string passed as
 * argument, passing its index as first argument.
 * Each character is passed by address to ’f’ to be modified if necessary.
 *
 * s: The string on which to iterate.
 * f: The function to apply to each character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}

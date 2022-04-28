/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:03 by jeulliot          #+#    #+#             */
/*   Updated: 2022/02/23 16:17:06 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_in(char c, char *set)
{
	size_t	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (c == set[j])
			return (1);
		j ++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*dest;
	size_t	len;
	size_t	j;
	size_t	k;

	len = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	j = 0;
	k = 0;
	while (ft_is_in(s1[len - 1], set) == 1 && len > 0)
		len --;
	while (ft_is_in(s1[j], set) == 1 && j < len)
		j ++;
	dest = malloc (sizeof(char) * (len - j + 1));
	if (dest)
	{
		while (j < len)
			dest[k++] = s1[j++];
		dest[k] = '\0';
	}
	free(s1);
	return (dest);
}

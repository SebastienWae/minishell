/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:06:36 by seb               #+#    #+#             */
/*   Updated: 2022/05/10 17:20:55 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*ft_strjoin_sep(const char *s1, const char *s2, const char *sep)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(s1, sep);
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

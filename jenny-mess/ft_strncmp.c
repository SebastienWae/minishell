/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:27:07 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/20 12:27:08 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

static int	ft_diff(unsigned int m, unsigned int n)
{
	if (m > n)
		return (1);
	if (m < n)
		return (-1);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (ft_diff(s1[i], s2[i]));
		i ++;
	}
	if (i == n)
		return (0);
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	if (s1[i] == '\0')
		return (-1);
	if (s2[i] == '\0')
		return (1);
	return (0);
}

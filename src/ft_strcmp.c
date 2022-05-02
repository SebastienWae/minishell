/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:09:52 by jeulliot          #+#    #+#             */
/*   Updated: 2022/01/23 19:17:36 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i] != '\0' && str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == str2[i])
			i++;
	}
	if (str1[i] == '\0' && str2[i] != '\0')
		return (-1);
	if (str1[i] != '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

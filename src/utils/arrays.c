/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:52:07 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 15:07:11 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <utils.h>
#include <stdio.h>

static void	array_destroy(t_array *self)
{
	*self = (t_array)
	{
		.len = 0,
		.values = NULL,
		.destroy = NULL
	};
	free(self);
}

void	array_print(t_array	*array)
{
	int	i;

	i = 0;
	while (array->values[i])
	{
		printf("array val #%d: %s\n", i, array->values[i]);
		i++;
	}
}

t_array	*array_constructor(void)
{
	t_array	*self;

	self = malloc(sizeof(t_array));
	*self = (t_array)
	{
		.len = 0,
		.values = NULL,
		.destroy = array_destroy
	};
	return (self);
}

void	array_push(t_array *arr, char *str)
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (arr->len + 2));
	if (!tmp)
		return ;
	while (i < arr->len)
	{
		tmp[i] = arr->values[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	free(arr->values);
	arr->values = tmp;
	arr->len++;
}

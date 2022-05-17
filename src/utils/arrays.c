/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:52:07 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 14:26:04 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <utils.h>

static void	array_destroy(t_array *self)
{
	while (self->len)
	{
		free(self->values[self->len]);
		self->len--;
	}
	*self = (t_array)
	{
		.len = 0,
		.values = NULL,
		.destroy = NULL
	};
	free(self);
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

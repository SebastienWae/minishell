/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:52:07 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 12:39:00 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <utils.h>
#include <stdio.h>

static void	array_destroy(t_array *self)
{
	while (self->len)
	{
		free(self->values[self->len - 1]);
		self->len--;
	}
	free(self->values);
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
	if (!self)
		return (NULL);
	*self = (t_array)
	{
		.len = 0,
		.values = NULL,
		.destroy = array_destroy
	};
	return (self);
}

void	array_remove(t_array **arr, size_t i)
{
	size_t	n;
	t_array	*new;

	n = 0;
	new = array_constructor();
	while (arr && n < (*arr)->len)
	{
		if (n != i)
			array_push(new, ft_strdup((*arr)->values[n]));
		n++;
	}
	(*arr)->destroy(*arr);
	*arr = new;
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

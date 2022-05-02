/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:57:06 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/02 16:13:58 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *data, int (*f)(void *, void *))
{
	while (lst && f)
	{
		if (f(lst->content, data))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

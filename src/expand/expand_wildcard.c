/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:48:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/19 15:13:27 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <dirent.h>
#include <expand.h>
#include <libft.h>
#include <utils.h>
#include <sys/types.h>
#include <unistd.h>

char	*expand_wildcard(t_tokenizer *t)
{
	DIR				*directory;
	struct dirent	*file;
	char			*c[3];
	t_token			*token;

	c[0] = NULL;
	c[1] = getcwd(NULL, 0);
	directory = opendir(c[1]);
	file = readdir(directory);
	while (file)
	{
		if (file->d_name[0] != '.')
		{
			token = token_constructor(T_TT_WORD, file->d_name);
			ft_lstadd_back(&(t->tokens), ft_lstnew(token));
		}
		file = readdir(directory);
	}
	free(c[1]);
	return (c[0]);
}

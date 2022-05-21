/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:48:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/21 14:08:47 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <expand.h>
#include <libft.h>

char	*expand_wildcard(t_tokenizer *t)
{
	DIR				*directory;
	struct dirent	*file;
	char			*c[3];
	t_token			*token;

	c[0] = NULL;
	c[1] = getcwd(NULL, 0);
	directory = opendir(c[1]);
	if (!directory)
		return (NULL);
	file = readdir(directory);
	while (file)
	{
		if (file->d_name[0] != '.')
		{
			token = token_constructor(T_TT_WORD, ft_strdup(file->d_name));
			ft_lstadd_back(&(t->tokens), ft_lstnew(token));
		}
		file = readdir(directory);
	}
	free(c[1]);
	closedir(directory);
	return (c[0]);
}

void	expand_var(t_expand *e)
{
	if (e->variable->end == 0)
	{
		if (e->str[e->cursor] != '_' && !ft_isalpha(e->str[e->cursor]))
		{
			expand_append_var(e);
			expand_append_char(e);
		}
		else
			e->variable->end++;
	}
	else
	{
		if (!ft_isalnum(e->str[e->cursor]) && e->str[e->cursor] != '_')
		{
			expand_append_var(e);
			expand_append_char(e);
		}
		else
			e->variable->end++;
	}
}

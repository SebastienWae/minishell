/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:33:11 by seb               #+#    #+#             */
/*   Updated: 2022/04/29 12:08:49 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>

static t_list	*add_token(t_token_type type, t_token_data data, t_list *tokens)
{
	t_token	*token;
	t_list	*tmp;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		if (tokens)
			free_tokens(tokens);
		return (NULL);
	}
	*token = (t_token){.type = type, .data = data};
	tmp = ft_lstnew(token);
	if (!tmp)
	{
		if (tokens)
			free_tokens(tokens);
		else if (token)
			free(token);
		return (NULL);
	}
	if (tokens)
		ft_lstadd_back(&tokens, tmp);
	else
		tokens = tmp;
	return (tokens);
}

void	free_tokens(t_list *tokens)
{
	t_list	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->content);
		tokens->next = NULL;
		free(tokens);
		tokens = tmp;
	}
}

t_list	*tokenizer(char *line)
{
	int					cursor;
	t_list				*tokens;
	union u_token_data	data;

	cursor = 0;
	tokens = NULL;
	while (line[cursor])
	{
		if (is_whitespace(line[cursor]))
			line[cursor] = 0;
		else if (is_metacharacter(line[cursor]))
		{
			data.c = line[cursor];
			tokens = add_token(METACHARACTER, data, tokens);
		}
		else if (!cursor || !line[cursor - 1]
			|| is_whitespace(line[cursor - 1])
			|| is_metacharacter(line[cursor - 1]))
		{
			data.word = &(line[cursor]);
			tokens = add_token(WORD, data, tokens);
		}
		cursor++;
	}
	return (tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:33:11 by seb               #+#    #+#             */
/*   Updated: 2022/04/29 17:49:58 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <libft.h>
#include <stdlib.h>

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
	int		cursor;
	t_list	*tokens;
	t_quote	quotes;

	cursor = 0;
	tokens = NULL;
	quotes.n = 0;
	while (line[cursor])
	{
		if (quotes.n && is_quote(line[cursor]))
			end_quote(&(line[cursor]), &quotes);
		else if (!quotes.n && is_quote(line[cursor]))
			start_quote(&(line[cursor]), &quotes, &tokens);
		else if (!quotes.n && is_whitespace(line[cursor]))
			line[cursor] = 0;
		else if (!quotes.n && is_metacharacter(line[cursor]))
			add_metacharacter(&(line[cursor]), &tokens);
		else if (!quotes.n && (!cursor || !line[cursor - 1]
				|| is_whitespace(line[cursor - 1])
				|| is_metacharacter(line[cursor - 1])))
			add_word(&(line[cursor]), &tokens);
		cursor++;
	}
	return (tokens);
}

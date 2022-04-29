/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:26:12 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/29 17:54:06 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <libft.h>
#include <stdlib.h>

t_list	*add_token(t_token_type type, t_token_data data, t_list *tokens)
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

void	add_metacharacter(char *c, t_list **tokens)
{
	union u_token_data	data;

	data.c = *c;
	*tokens = add_token(METACHARACTER, data, *tokens);
	*c = 0;
}

void	add_word(char *word, t_list **tokens)
{
	union u_token_data	data;

	data.word = word;
	*tokens = add_token(WORD, data, *tokens);
}

void	end_quote(char *quote, t_quote *quotes)
{
	if (*quote == '"'
		&& quotes->type == DOUBLE_QUOTE)
	{
		quotes->n = 0;
		*quote = 0;
	}
	else if (*quote == '\''
		&& quotes->type == SINGLE_QUOTE)
	{
		quotes->n = 0;
		*quote = 0;
	}
}

void	start_quote(char *quote, t_quote *quotes, t_list **tokens)
{
	union u_token_data	data;

	data.word = quote + 1;
	if (*quote == '"')
	{
		*tokens = add_token(DOUBLE_QUOTE, data, *tokens);
		quotes->type = DOUBLE_QUOTE;
	}
	else if (*quote == '\'')
	{
		*tokens = add_token(SINGLE_QUOTE, data, *tokens);
		quotes->type = SINGLE_QUOTE;
	}
	*quote = 0;
	quotes->n = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/03 18:27:06 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>

//TODO: implement
void	free_tokens(t_tokens *tokens)
{
	(void)tokens;
}

//TODO: set state to err
void	*add_token(t_token_type type, t_token_data data, t_tokens *tokens)
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
	if (tokens->tokens)
		ft_lstadd_back(&(tokens->tokens), tmp);
	else
		tokens->tokens = tmp;
	return (tokens);
}

void	tokenizer_next(t_tokens *tokens, t_token_event e)
{
	int						n_states;
	static t_token_machine	state_machine[] = {
	{ST_T_INIT, tokenizer_init},
	{ST_T_IN_DOUBLE_QUOTE, tokenizer_in_double_quote},
	{ST_T_IN_SINGLE_QUOTE, tokenizer_in_single_quote},
	{ST_T_IN_WORD, tokenizer_in_word},
	{ST_T_IN_METACHAR, tokenizer_in_metachar}
	};

	n_states = ST_T_ERROR;
	while (n_states--)
	{
		if (state_machine[n_states].state == tokens->state)
			state_machine[n_states].handler(tokens, e);
	}
	if (n_states < 0)
		tokens->state = ST_T_ERROR;
}

t_list	*tokenizer(char *line)
{
	t_tokens		tokens;

	tokens.tokens = NULL;
	tokens.cursor = 0;
	tokens.line = line;
	tokens.state = ST_T_INIT;
	while (tokens.line[tokens.cursor] && tokens.state != ST_T_ERROR)
	{
		if (tokens.line[tokens.cursor] == '\'')
			tokenizer_next(&tokens, E_T_SINGLE_QUOTE);
		else if (tokens.line[tokens.cursor] == '"')
			tokenizer_next(&tokens, E_T_DOUBLE_QUOTE);
		else if (is_whitespace(tokens.line[tokens.cursor]))
			tokenizer_next(&tokens, E_T_WHITESPACE);
		else if (is_metacharacter(tokens.line[tokens.cursor]))
			tokenizer_next(&tokens, E_T_METACHAR);
		else
			tokenizer_next(&tokens, E_T_CHAR);
	}
	return (tokens.tokens);
}

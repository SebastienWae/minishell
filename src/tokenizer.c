/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 17:47:53 by swaegene         ###   ########.fr       */
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

// TODO: catch error event/state
// TODO: catch unimplemented event
// TODO: catch end event
void	tokenizer_next(t_tokens *tokens, t_token_event e)
{
	int						n_states;
	static t_token_machine	state_machine[] = {
	{S_T_NOT_TOKEN, tokenizer_state_not_token},
	{S_T_IN_WORD, tokenizer_state_in_word},
	{S_T_IN_OPERATOR, tokenizer_state_in_operator},
	{S_T_IN_SINGLE_QUOTE, tokenizer_state_in_single_quote},
	{S_T_IN_DOUBLE_QUOTE, tokenizer_state_in_double_quote},
	{S_T_ERROR, NULL},
	{S_T_FINISHED, NULL},
	};

	n_states = S_T_ERROR;
	while (n_states--)
	{
		if (state_machine[n_states].state == tokens->state)
			state_machine[n_states].handler(tokens, e);
	}
	if (n_states < 0)
		tokens->state = S_T_ERROR;
}

t_list	*tokenizer(char *line)
{
	t_tokens		tokens;

	tokens = tokens_constructor(line);
	while (tokens.state != S_T_FINISHED)
	{
		if (tokens.state == S_T_ERROR)
			tokenizer_next(&tokens, E_T_ERROR);
		if (tokens.line[tokens.end_cursor] == '\0')
			tokenizer_next(&tokens, E_T_END);
		else if (tokens.line[tokens.end_cursor] == '\'')
			tokenizer_next(&tokens, E_T_SINGLE_QUOTE);
		else if (tokens.line[tokens.end_cursor] == '"')
			tokenizer_next(&tokens, E_T_DOUBLE_QUOTE);
		else if (is_operator(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_OPERATOR);
		else if (is_whitespace(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_WHITESPACE);
		else if (is_unimplemented(tokens.line[tokens.end_cursor]))
			tokenizer_next(&tokens, E_T_UNIMPLEMENTED);
		else
			tokenizer_next(&tokens, E_T_CHAR);
	}
	return (tokens.tokens);
}

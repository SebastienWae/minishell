/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:44:15 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/04 21:53:14 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <tokenizer.h>

//TODO: implement
static void	tokenizer_error(t_tokens *tokens)
{
	(void)tokens;
}

//TODO: implement
static void	tokenizer_unimplemented(t_tokens *tokens)
{
	(void)tokens;
}

void	tokenizer_next(t_tokens *tokens, t_token_event e)
{
	static t_token_machine	state_machine[] = {
	{.state = S_T_NOT_TOKEN,		.handler = tokenizer_state_not_token},
	{.state = S_T_IN_WORD,			.handler = tokenizer_state_in_word},
	{.state = S_T_IN_OPERATOR,		.handler = tokenizer_state_in_operator},
	{.state = S_T_IN_SINGLE_QUOTE,	.handler = tokenizer_state_in_single_quote},
	{.state = S_T_IN_DOUBLE_QUOTE,	.handler = tokenizer_state_in_double_quote},
	{.state = S_T_ERROR,			.handler = tokenizer_error},
	{.state = S_T_FINISHED,			.handler = tokenizer_error},
	};

	tokens->last_event = e;
	if (e == E_T_UNIMPLEMENTED)
		tokenizer_unimplemented(tokens);
	else if (sizeof(state_machine) > tokens->state)
		state_machine[tokens->state].handler(tokens);
	else
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
	return (tokens.list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:46:15 by seb               #+#    #+#             */
/*   Updated: 2022/05/07 21:59:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <tokenizer.h>
#include <stdio.h>

void	print_token(t_token *token, int n)
{
	static char	*token_types[] = {"NONE", "WORD", "PIPE", "HEREDOC",
		"REDIRECTION IN", "REDIRECTION OUT", "REDIRECTION APPEND",
		"SINGLE QUOTE", "DOUBLE QUOTE", "SYNTAX ERROR"};

	if (n)
	{
		printf("  token #%d\n", n);
		printf("    - value: %s\n", token->str);
		printf("    - type: %s\n", token_types[token->type]);
	}
	else
	{
		printf("token value: %s\n", token->str);
		printf("token type: %s\n", token_types[token->type]);
	}
}

void	print_tokenizer(t_tokenizer *tokenizer)
{
	int			n;
	t_list		*token;
	static char	*tokenizer_states[] = {"NONE", "WORKING", "ERROR", "FINISHED"};

	printf("### DEBUG: TOKENIZER\n");
	printf("- tokens:\n");
	token = tokenizer->tokens;
	n = 1;
	while (token)
	{
		print_token((t_token *)token->content, n++);
		token = token->next;
	}
	printf("- line: %s\n", tokenizer->line);
	printf("- cursor: %d\n", tokenizer->cursor);
	if (tokenizer->curr_token)
		print_token(tokenizer->curr_token, 0);
	else
		printf("- current token: (NULL)\n");
	printf("- state: %s\n", tokenizer_states[tokenizer->state]);
}

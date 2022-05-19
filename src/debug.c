/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:46:15 by seb               #+#    #+#             */
/*   Updated: 2022/05/19 14:27:00 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdio.h>
#include <tokenizer.h>
#include <utils.h>

void	print_redir(t_redir *redir)
{
	static char	*redir_types[] = {"NONE", "IN", "OUT", "HEREDOC", "APPEND"};

	printf("		 - type: %s\n", redir_types[redir->type]);
	printf("		 - target: %s\n", redir->target);
}

void	print_cmd(t_cmd *cmd)
{
	int		n;
	t_list	*in;
	t_list	*out;

	in = cmd->in;
	out = cmd->out;
	printf("    - cmd:\n");
	printf("    - piped: %d\n", cmd->piped);
	printf("    - redir in:\n");
	n = 1;
	while (in)
	{
		printf("		- redir in #%d\n", n++);
		print_redir(in->content);
		in = in->next;
	}
	printf("    - redir out:\n");
	n = 1;
	while (out)
	{
		printf("		- redir out #%d\n", n++);
		print_redir(out->content);
		out = out->next;
	}
}

void	print_parser(t_parser *parser)
{
	int			n;
	t_list		*cmds;
	static char	*parser_states[] = {"NONE", "WORKING", "ERROR", "FINISHED"};
	static char	*token_types[] = {"NONE", "WORD", "PIPE", "HEREDOC",
		"REDIRECTION IN", "REDIRECTION OUT", "REDIRECTION APPEND",
		"SINGLE QUOTE", "DOUBLE QUOTE", "SYNTAX ERROR"};

	printf("### DEBUG: PARSER\n");
	printf("- cmds:\n");
	cmds = parser->cmds;
	n = 1;
	while (cmds)
	{
		printf("  - cmd #%d\n", n++);
		print_cmd(cmds->content);
		cmds = cmds->next;
	}
	printf("- current cmd:\n");
	if (parser->curr_cmd)
		print_cmd(parser->curr_cmd);
	else
		printf("	- (NULL)\n");
	printf("- last token type: %s\n", token_types[parser->last_token_type]);
	printf("- state: %s\n", parser_states[parser->state]);
}

void	print_token(t_token *token)
{
	static char	*token_types[] = {"NONE", "WORD", "PIPE", "HEREDOC",
		"REDIRECTION IN", "REDIRECTION OUT", "REDIRECTION APPEND",
		"SINGLE QUOTE", "DOUBLE QUOTE", "SYNTAX ERROR"};

	printf("    - value: %s\n", token->str);
	printf("    - type: %s\n", token_types[token->type]);
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
		printf("  - token #%d\n", n++);
		print_token((t_token *)token->content);
		token = token->next;
	}
	printf("- line: %s\n", tokenizer->line);
	printf("- cursor: %d\n", tokenizer->cursor);
	printf("- current token:\n");
	if (tokenizer->curr_token)
		print_token(tokenizer->curr_token);
	else
		printf("	(NULL)\n");
	printf("- state: %s\n", tokenizer_states[tokenizer->state]);
}

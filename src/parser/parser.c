/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:55:23 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 20:06:15 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <tokenizer.h>
#include <parser.h>

static void	cmd_destructor(t_cmd *self)
{
	free(self->cmd);
	ft_lstclear(&(self->in), free);
	ft_lstclear(&(self->out), free);
	*self = (t_cmd)
	{
		.cmd = NULL,
		.in = NULL,
		.out = NULL,
		.piped = 0,
		.destructor = NULL
	};
	free(self);
}

t_cmd	*cmd_constructor(void)
{
	t_cmd	*self;

	self = malloc(sizeof(t_cmd));
	if (!self)
		return (NULL);
	*self = (t_cmd)
	{
		.cmd = NULL,
		.in = NULL,
		.out = NULL,
		.piped = 0,
		.destructor = cmd_destructor
	};
	return (self);
}

static void	parser_destructor(t_parser *self)
{
	t_list	*tmp;

	while (self->cmds)
	{
		tmp = self->cmds->next;
		((t_cmd *)self->cmds->content)->destructor(self->cmds->content);
		free(self->cmds);
		self->cmds = tmp;
	}
	if (self->curr_cmd)
		self->curr_cmd->destructor(self->curr_cmd);
	*self = (t_parser)
	{
		.cmds = NULL,
		.curr_cmd = NULL,
		.last_token_type = 0,
		.state = 0,
		.destructor = NULL
	};
	free(self);
}

static t_parser	*parser_constructor(void)
{
	t_parser	*self;

	self = malloc(sizeof(t_parser));
	if (!self)
		return (NULL);
	*self = (t_parser)
	{
		.cmds = NULL,
		.curr_cmd = NULL,
		.last_token_type = 0,
		.state = P_S_WORKING,
		.destructor = parser_destructor
	};
	return (self);
}

t_parser	*parse(t_tokenizer *tokenizer)
{
	t_parser	*parser;
	t_list		*tokens;

	parser = parser_constructor();
	tokens = tokenizer->tokens;
	while (parser->state == P_S_WORKING)
	{
		if (!tokens)
		{
			parser_end_cmd(parser);
			break ;
		}
		else if (((t_token *)tokens->content)->type == T_TT_WORD)
			parser_word_handler(parser, tokens->content);
		else if (((t_token *)tokens->content)->type == T_TT_PIPE)
			parser_pipe_handler(parser, tokens->content);
		else if (((t_token *)tokens->content)->type == T_TT_HEREDOC)
			parser_heredoc_handler(parser, tokens->content);
		else if (((t_token *)tokens->content)->type == T_TT_REDIRECTION_IN)
			parser_redirection_in_handler(parser, tokens->content);
		else if (((t_token *)tokens->content)->type == T_TT_REDIRECTION_OUT)
			parser_redirection_out_handler(parser, tokens->content);
		else if (((t_token *)tokens->content)->type == T_TT_REDIRECTION_APPEND)
			parser_redirection_append_handler(parser, tokens->content);
		else
			parser_syntax_error(parser, tokens->content);
		tokens = tokens->next;
	}
	return (parser);
}

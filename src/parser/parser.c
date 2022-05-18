/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:55:23 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/18 13:28:21 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <stdlib.h>
#include <tokenizer.h>

static void	cmd_destructor(t_cmd *self)
{
	self->cmd->destroy(self->cmd);
	ft_lstclear(&(self->in), free);
	ft_lstclear(&(self->out), free);
	*self = (t_cmd){
		.cmd = NULL,
		.in = NULL,
		.out = NULL,
		.piped = 0,
		.destroy = NULL};
	free(self);
}

t_cmd	*cmd_constructor(void)
{
	t_cmd	*self;

	self = malloc(sizeof(t_cmd));
	if (!self)
		return (NULL);
	*self = (t_cmd){
		.cmd = NULL,
		.in = NULL,
		.out = NULL,
		.piped = 0,
		.destroy = cmd_destructor};
	return (self);
}

static void	parser_destructor(t_parser *self)
{
	t_list	*tmp;

	while (self->cmds)
	{
		tmp = self->cmds->next;
		((t_cmd *)self->cmds->content)->destroy(self->cmds->content);
		free(self->cmds);
		self->cmds = tmp;
	}
	if (self->curr_cmd)
		self->curr_cmd->destroy(self->curr_cmd);
	*self = (t_parser){
		.cmds = NULL,
		.curr_cmd = NULL,
		.last_token_type = 0,
		.state = 0,
		.tokens = NULL,
		.shell = NULL,
		.destroy = NULL};
	free(self);
}

static t_parser	*parser_constructor(t_list *tokens, t_minishell *shell)
{
	t_parser	*self;

	self = malloc(sizeof(t_parser));
	if (!self)
		return (NULL);
	*self = (t_parser){
		.cmds = NULL,
		.curr_cmd = NULL,
		.last_token_type = 0,
		.state = P_S_WORKING,
		.tokens = tokens,
		shell,
		.destroy = parser_destructor};
	return (self);
}

t_parser	*parse(t_tokenizer *tokenizer, t_minishell *shell)
{
	t_parser	*p;

	p = parser_constructor(tokenizer->tokens, shell);
	if (!p)
		return (NULL);
	while (p->state == P_S_WORKING)
	{
		if (!p->tokens)
			parser_end(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_WORD)
			parser_word_handler(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_PIPE)
			parser_pipe_handler(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_HEREDOC)
			parser_heredoc_handler(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_REDIR_IN)
			parser_redirection_in_handler(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_REDIR_OUT)
			parser_redirection_out_handler(p);
		else if (((t_token *)p->tokens->content)->type == T_TT_REDIR_APPEND)
			parser_redirection_append_handler(p);
		else
			parser_syntax_error(p);
	}
	return (p);
}

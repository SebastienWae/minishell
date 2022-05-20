/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:35:35 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 16:12:12 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <libft.h>
#include <parser.h>
#include <stdlib.h>
#include <tokenizer.h>

static t_redir	redir_heredoc(t_parser *p)
{
	t_redir		redir;
	t_expand	*unquoted;

	unquoted = expand(((t_token *)p->tokens->content)->str, E_QUOTE,
			p->shell);
	if (ft_strcmp(unquoted->result, ((t_token *)p->tokens->content)->str))
	{
		redir.type = P_RT_HEREDOC_QUOTED;
		redir.target = unquoted->result;
	}
	else
	{
		redir.type = P_RT_HEREDOC;
		redir.target = unquoted->result;
	}
	unquoted->destroy(unquoted);
	return (redir);
}

static t_redir	*redir_constructor(t_parser *p)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (p->last_token_type == T_TT_HEREDOC)
		*redir = redir_heredoc(p);
	else
	{
		if (p->last_token_type == T_TT_REDIR_IN)
			redir->type = P_RT_IN;
		else if (p->last_token_type == T_TT_REDIR_OUT)
			redir->type = P_RT_OUT;
		else if (p->last_token_type == T_TT_REDIR_APPEND)
			redir->type = P_RT_APPEND;
		redir->target = ((t_token *)p->tokens->content)->str;
	}
	return (redir);
}

static void	parser_add_redir(t_parser *p, t_redir *redir)
{
	t_list	*tmp;

	tmp = ft_lstnew(redir);
	if (!tmp)
	{
		p->state = P_S_ERROR;
		return ;
	}
	if (p->last_token_type == T_TT_REDIR_IN
		|| p->last_token_type == T_TT_HEREDOC)
	{
		if (p->curr_cmd->in)
			ft_lstadd_back(&(p->curr_cmd->in), tmp);
		else
			p->curr_cmd->in = tmp;
	}
	else if (p->last_token_type == T_TT_REDIR_OUT
		|| p->last_token_type == T_TT_REDIR_APPEND)
	{
		if (p->curr_cmd->out)
			ft_lstadd_back(&(p->curr_cmd->out), tmp);
		else
			p->curr_cmd->out = tmp;
	}
}

void	parser_new_redir(t_parser *p)
{
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_set_redir(t_parser *p)
{
	t_redir	*redir;

	redir = redir_constructor(p);
	if (!redir)
	{
		p->state = P_S_ERROR;
		return ;
	}
	parser_add_redir(p, redir);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

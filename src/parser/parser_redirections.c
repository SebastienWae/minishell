/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:35:35 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 13:41:53 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <stdlib.h>
#include <tokenizer.h>

static t_redir	*redir_constructor(t_token_type type, char *target)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (type == T_TT_REDIRECTION_IN)
		redir->type = P_RT_IN;
	else if (type == T_TT_REDIRECTION_OUT)
		redir->type = P_RT_OUT;
	else if (type == T_TT_HEREDOC)
		redir->type = P_RT_HEREDOC;
	else if (type == T_TT_REDIRECTION_APPEND)
		redir->type = P_RT_APPEND;
	redir->target = target;
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
	if (p->last_token_type == T_TT_REDIRECTION_IN
		|| p->last_token_type == T_TT_HEREDOC)
	{
		if (p->curr_cmd->in)
			ft_lstadd_back(&(p->curr_cmd->in), tmp);
		else
			p->curr_cmd->in = tmp;
	}
	else if (p->last_token_type == T_TT_REDIRECTION_OUT
		|| p->last_token_type == T_TT_REDIRECTION_APPEND)
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

	redir = redir_constructor(p->last_token_type,
			((t_token *)p->tokens->content)->str);
	if (!redir)
	{
		p->state = P_S_ERROR;
		return ;
	}
	parser_add_redir(p, redir);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

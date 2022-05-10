/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:35:35 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 20:17:24 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <libft.h>
#include <parser.h>
#include <stdlib.h>

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

void	parser_new_redir(t_parser *p, t_token *t)
{
	p->last_token_type = t->type;
}

void	parser_set_redir(t_parser *p, t_token *t)
{
	t_redir	*redir;
	t_list	*tmp;

	redir = redir_constructor(p->last_token_type, t->str);
	if (!redir)
		return ; //TODO: handle error
	tmp = ft_lstnew(redir);
	if (!tmp)
		return ; //TODO: handle error
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
	p->last_token_type = t->type;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/16 18:03:41 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <tokenizer.h>

void	parser_add_to_cmd(t_parser *p)
{
	char	*tmp;

	if (p->curr_cmd->cmd)
	{
		tmp = p->curr_cmd->cmd;
		p->curr_cmd->cmd = ft_strjoin_sep(p->curr_cmd->cmd,
				((t_token *)p->tokens->content)->str, " ");
		free(tmp);
	}
	else
		p->curr_cmd->cmd = ft_strdup(((t_token *)p->tokens->content)->str);
	if (!(p->curr_cmd->cmd))
	{
		p->state = P_S_ERROR;
		return ;
	}
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_new_cmd(t_parser *p)
{
	t_cmd	*cmd;

	parser_end_cmd(p);
	cmd = cmd_constructor();
	if (((t_token *)p->tokens->content)->type == T_TT_WORD)
		cmd->cmd = ft_strdup(((t_token *)p->tokens->content)->str);
	p->curr_cmd = cmd;
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_end_cmd(t_parser *p)
{
	t_list		*tmp;
	t_expand	*e;

	if (p->curr_cmd)
	{
		e = expand(p->curr_cmd->cmd, E_VARIABLE | E_UNQUOTE, p->shell);
		if (e && e->result)
		{
			tmp = ft_lstnew(e->result);
			if (!tmp)
			{
				p->state = P_S_ERROR;
				return ;
			}
			ft_lstadd_back(&(p->cmds), tmp);
		}
	}
	p->curr_cmd = NULL;
}

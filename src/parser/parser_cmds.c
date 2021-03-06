/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 15:05:51 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <parser.h>

void	parser_add_to_cmd(t_parser *p)
{
	if (!(p->curr_cmd->cmd))
		p->curr_cmd->cmd = array_constructor();
	if (!(p->curr_cmd->cmd))
	{
		p->state = P_S_ERROR;
		return ;
	}
	array_push(p->curr_cmd->cmd, ((t_token *)p->tokens->content)->str);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

void	parser_new_cmd(t_parser *p)
{
	t_cmd	*cmd;

	parser_end_cmd(p);
	cmd = cmd_constructor();
	p->curr_cmd = cmd;
	if (((t_token *)p->tokens->content)->type == T_TT_WORD)
		parser_add_to_cmd(p);
	p->last_token_type = ((t_token *)p->tokens->content)->type;
}

static void	parser_expand_cmd(t_parser *p)
{
	int			i;
	int			y;
	char		**values;
	t_expand	*e;

	i = 0;
	y = 0;
	values = p->curr_cmd->cmd->values;
	while (values[i])
	{
		e = expand(values[i], E_VAR_QUOTE, p->shell);
		if (e)
		{
			if (e->result)
				values[y++] = e->result;
			e->destroy(e);
		}
		i++;
	}
	p->curr_cmd->cmd->len = y;
	values[y] = NULL;
}

void	parser_end_cmd(t_parser *p)
{
	t_list	*tmp;

	if (p->curr_cmd)
	{
		if (p->curr_cmd->cmd)
		{
			parser_expand_cmd(p);
			expand_wildcard(p);
		}
		tmp = ft_lstnew(p->curr_cmd);
		if (!tmp)
		{
			p->state = P_S_ERROR;
			return ;
		}
		ft_lstadd_back(&(p->cmds), tmp);
	}
	p->curr_cmd = NULL;
}

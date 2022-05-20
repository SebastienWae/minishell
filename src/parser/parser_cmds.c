/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 13:32:52 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <stddef.h>
#include <tokenizer.h>
#include <utils.h>

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
	char		**values;
	t_expand	*e;

	i = 0;
	values = p->curr_cmd->cmd->values;
	while (values[i])
	{
		e = expand(values[i], E_VAR_QUOTE, p->shell);
		if (e)
		{
			values[i] = e->result;
			e->destroy(e);
		}
		i++;
	}
	values[i++] = NULL;
	p->curr_cmd->cmd->len = i;
}

void	parser_end_cmd(t_parser *p)
{
	t_list	*tmp;

	if (p->curr_cmd)
	{
		if (p->curr_cmd->cmd)
			parser_expand_cmd(p);
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

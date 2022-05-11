/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 09:01:23 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <libft.h>
#include <minishell.h>
#include <parser.h>

void	parser_add_to_cmd(t_parser *p, t_token *t)
{
	char	*tmp;

	if (p->curr_cmd->cmd)
	{
		tmp = p->curr_cmd->cmd;
		p->curr_cmd->cmd = ft_strjoin_sep(p->curr_cmd->cmd, t->str, " ");
		free(tmp);
	}
	else
		p->curr_cmd->cmd = ft_strdup(t->str);
	if (!(p->curr_cmd->cmd))
		return ; // TODO: handle erro
	p->last_token_type = t->type;
}

void	parser_new_cmd(t_parser *p, t_token *t)
{
	t_cmd	*cmd;

	parser_end_cmd(p);
	cmd = cmd_constructor();
	if (t->type == T_TT_WORD)
		cmd->cmd = ft_strdup(t->str);
	p->curr_cmd = cmd;
	p->last_token_type = t->type;
}

void	parser_end_cmd(t_parser	*p)
{
	t_list	*tmp;

	if (p->curr_cmd)
	{
		tmp = ft_lstnew(p->curr_cmd);
		if (!tmp)
			return ; // TODO: handle error
		ft_lstadd_back(&(p->cmds), tmp);
	}
	p->curr_cmd = NULL;
}

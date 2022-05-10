/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:31:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/10 20:03:51 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>
#include <libft.h>
#include <minishell.h>
#include <parser.h>

void	parser_add_to_cmd(t_parser *p, t_token *t)
{
	char	*tmp;

	tmp = p->curr_cmd->cmd;
	p->curr_cmd->cmd = ft_strjoin_sep(p->curr_cmd->cmd, t->str, " ");
	if (!(p->curr_cmd->cmd))
		return ; // TODO: handle erro
	free(tmp);
	p->last_token_type = t->type;
}

void	parser_new_cmd(t_parser *p, t_token *t)
{
	t_cmd	*cmd;

	parser_end_cmd(p);
	cmd = cmd_constructor();
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

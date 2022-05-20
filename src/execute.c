/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:35:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 17:11:42 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <stdio.h>
#include <readline/history.h>
#include <sys.h>
#include <tokenizer.h>

static void	memory_err(char *err)
{
	ft_putstr_fd(err, 2);
	exit(1);
}

static t_parser	*get_cmds(char *str, t_minishell *shell)
{
	t_parser	*parsed;
	t_tokenizer	*token;

	token = tokenize(str);
	if (!token)
	{
		free(str);
		memory_err("Memory allocation failed. Aborting");
	}
	parsed = parse(token, shell);
	if (!parsed)
	{
		free(str);
		memory_err("Memory allocation failed. Aborting");
	}
	if (token->state == T_S_ERROR || parsed->state == P_S_ERROR)
	{
		token->destroy(token);
		parsed->destroy(parsed);
		g_out = 2;
		free(str);
		return (NULL);
	}
	token->destroy(token);
	return (parsed);
}

static void	execute_cmd(t_list *c, t_minishell *s, t_parser *p)
{
	t_fd_in_out	f;

	while (c)
	{
		f = ft_fd_manager((t_cmd *)(c->content), 0, *s);
		if (f.in != -1 && f.out != -1)
			ft_launch_cmd(((t_cmd *)(c->content))->cmd->values, *s, p);
		if (f.in != 0)
			close(f.in);
		if (f.out != 1)
			close(f.out);
		ft_reset_fd(*s);
		c = c->next;
	}
}

void	execute_cmds(char *str, t_minishell *shell)
{
	t_parser	*parsed;
	t_list		*cmd;

	if (str[0] != 0)
	{
		add_history(str);
		parsed = get_cmds(str, shell);
		if (!parsed)
			return ;
		cmd = parsed->cmds;
		if (cmd && ((t_cmd *)(cmd->content))->piped == 1)
			ft_pipe(*shell, cmd);
		else if (cmd && ((t_cmd *)(cmd->content))->cmd
				&& ((t_cmd *)(cmd->content))->cmd->values)
			execute_cmd(cmd, shell, parsed);
		else if (cmd && (((t_cmd *)(cmd->content))->in
			|| ((t_cmd *)(cmd->content))->out))
			ft_fd_manager((t_cmd *)(cmd->content), 0, *shell);
		ft_reset_fd(*shell);
		parsed->destroy(parsed);
	}
}

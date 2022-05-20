/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:35:42 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/20 20:32:57 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <parser.h>
#include <stdio.h>
#include <readline/history.h>
#include <sys.h>
#include <tokenizer.h>

static t_tokenizer	*get_tokens(char *str)
{
	t_tokenizer	*tokens;

	tokens = tokenize(str);
	free(str);
	if (!tokens)
	{
		ft_putstr_fd("Memory allocation failed. Aborting", 2);
		exit(1);
	}
	if (tokens->state == T_S_ERROR)
	{
		tokens->destroy(tokens);
		g_out = 2;
		return (NULL);
	}
	return (tokens);
}

static t_parser	*get_cmds(t_tokenizer *tokens, t_minishell *shell)
{
	t_parser	*parsed;

	parsed = parse(tokens, shell);
	if (!parsed)
	{
		ft_putstr_fd("Memory allocation failed. Aborting", 2);
		exit(1);
	}
	if (parsed->state == P_S_ERROR)
	{
		tokens->destroy(tokens);
		parsed->destroy(parsed);
		g_out = 2;
		return (NULL);
	}
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

static void	execute_no_cmd(t_list *cmd, t_minishell *shell)
{
	t_fd_in_out	fd;

	fd = ft_fd_manager((t_cmd *)(cmd->content), 0, *shell);
	if (fd.in != 0)
		close(fd.in);
	if (fd.out != 1)
		close(fd.out);
}

void	execute_cmds(char *str, t_minishell *shell)
{
	t_tokenizer	*tokens;
	t_parser	*parsed;
	t_list		*cmd;

	add_history(str);
	tokens = get_tokens(str);
	if (!tokens)
		return ;
	parsed = get_cmds(tokens, shell);
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
		execute_no_cmd(cmd, shell);
	ft_reset_fd(*shell);
	tokens->destroy(tokens);
	parsed->destroy(parsed);
}

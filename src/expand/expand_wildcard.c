/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:48:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 15:12:51 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <dirent.h>
#include <expand.h>
#include <stdlib.h>

static void	wild_only_wild(struct s_wild w, int **l)
{
	int	p_cur;

	p_cur = 1;
	while (p_cur <= w.expr_len)
	{
		if (w.expr[p_cur - 1] == '*')
			l[0][p_cur] = l[0][p_cur - 1];
		p_cur++;
	}
}

static int	wild_is_match(struct s_wild w, int **l)
{
	int	s_cur;
	int	p_cur;

	wild_only_wild(w, l);
	s_cur = 1;
	while (s_cur <= w.str_len)
	{
		p_cur = 1;
		while (p_cur <= w.expr_len)
		{
			if (w.expr[p_cur - 1] == '*')
				l[s_cur][p_cur] = (l[s_cur][p_cur - 1] || l[s_cur - 1][p_cur]);
			else if (w.str[s_cur - 1] == w.expr[p_cur - 1])
				l[s_cur][p_cur] = l[s_cur - 1][p_cur - 1];
			else
				l[s_cur][p_cur] = 0;
			p_cur++;
		}
		s_cur++;
	}
	if (l[w.str_len][w.expr_len])
		return (1);
	return (0);
}

static int	wild_check_match(struct s_wild w)
{
	int	match;
	int	i;
	int	**lookup;

	lookup = ft_calloc(w.str_len + 1, sizeof(int *));
	i = 0;
	while (i <= w.str_len)
	{
		lookup[i] = ft_calloc(w.expr_len + 1, sizeof(int));
		i++;
	}
	lookup[0][0] = 1;
	match = wild_is_match(w, lookup);
	i = 0;
	while (i <= w.str_len)
	{
		free(lookup[i]);
		i++;
	}
	free(lookup);
	return (match);
}

static void	wild_replace(char *expr, char *str, int index, t_parser *p)
{
	int				i;
	struct s_wild	w;
	t_array			*new;

	w = (struct s_wild)
	{
		str, expr,
		.str_len = ft_strlen(str),
		.expr_len = ft_strlen(expr),
	};
	if (wild_check_match(w))
	{
		i = 0;
		new = array_constructor();
		while (p->curr_cmd->cmd->values[i])
		{
			array_push(new, ft_strdup(p->curr_cmd->cmd->values[i]));
			if (index == i)
				array_push(new, ft_strdup(str));
			i++;
		}
		p->curr_cmd->cmd->destroy(p->curr_cmd->cmd);
		p->curr_cmd->cmd = new;
	}
}

void	expand_wildcard(t_parser *p)
{
	size_t	i;
	size_t	fn;
	char	**files;
	int		is_wild;

	files = get_files_name();
	if (!files)
		return ;
	i = 0;
	while (i < p->curr_cmd->cmd->len)
	{
		fn = 0;
		is_wild = wild_is_present(p->curr_cmd->cmd->values[i]);
		while (files[fn])
		{
			if (is_wild
				&& wild_check_glob(p->curr_cmd->cmd->values[i], files[fn]))
				wild_replace(p->curr_cmd->cmd->values[i], files[fn], i, p);
			fn++;
		}
		if (is_wild)
			array_remove(&(p->curr_cmd->cmd), i);
		i++;
	}
	free_file_names(files);
}

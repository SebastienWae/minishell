/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:15:20 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 14:33:53 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <parser.h>
# include <minishell.h>

typedef enum e_expand_state			t_expand_state;
typedef enum e_expand_flag			t_expand_flag;
typedef struct s_expand				t_expand;
typedef struct s_expand_handlers	t_expand_handlers;
typedef struct s_variable			t_variable;

enum	e_expand_flag
{
	E_QUOTE = 1,
	E_VAR,
	E_VAR_QUOTE,
	E_FORCE_VAR
};

enum	e_expand_state
{
	E_S_EXPANDING = 1,
	E_S_IN_SINGLE_QUOTE,
	E_S_IN_DOUBLE_QUOTE,
	E_S_FINISHED,
	E_S_ERROR
};

struct s_variable
{
	int	start;
	int	end;
};

struct s_expand
{
	char			*str;
	int				flags;
	t_minishell		*shell;
	char			*result;
	int				cursor;
	t_variable		*variable;
	t_expand_state	state;
	void			(*destroy)(t_expand *);
};

struct	s_expand_handlers
{
	t_expand_state	state;
	t_expand_state	(*handler)(char *, int);
	t_expand_state	next_state;
};

struct	s_wild
{
	char	*str;
	char	*expr;
	int		str_len;
	int		expr_len;
};

t_expand	*expand(char *str, t_expand_flag f, t_minishell *shell);

t_variable	*variable_constructor(int start);

void		expand_single_quote_handler(t_expand *e);
void		expand_double_quote_handler(t_expand *e);
void		expand_var_handler(t_expand *e);
void		expand_space_handler(t_expand *e);
void		expand_char_handler(t_expand *e);

void		expand_append_char(t_expand *e);
void		expand_append_var(t_expand *e);
void		expand_add_empty(t_expand *e);
void		expand_finish(t_expand *e);

void		expand_wildcard(t_parser *p);
void		expand_var(t_expand *e);
void		expand_replace_wildcard(char *str);

int			wild_is_present(char *str);
char		**get_files_name(void);
void		free_file_names(char **files);
int			wild_check_glob(char *expr, char *file);
#endif

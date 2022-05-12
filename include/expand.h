/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 15:51:49by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef enum e_expand_state			t_expand_state;
typedef struct s_expand				t_expand;
typedef struct s_expand_handlers	t_expand_handlers;
typedef struct s_variable			t_variable;

#define E_UNQUOTE (1 << 1)
#define E_VARIABLE (1 << 2)

enum	e_expand_state
{
	E_S_IN_WORD = 1,
	E_S_IN_SINGLE_QUOTE,
	E_S_IN_DOUBLE_QUOTE,
	E_S_FINISHED
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
	char			*result;
	int				cursor;
	t_variable		*variable;
	t_expand_state	state;
	void			(*destructor)(t_expand *);
};

struct	s_expand_handlers
{
	t_expand_state	state;
	t_expand_state	(*handler)(char *, int);
	t_expand_state	next_state;
};

t_expand	*expand(char *str, int flags);

t_variable	*variable_constructor(int start, int end);

void		expand_quote_handler(t_expand *e);
void		expand_var_handler(t_expand *e);
void		expand_space_handler(t_expand *e);
void		expand_char_handler(t_expand *e);

#endif

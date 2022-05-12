/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:07:25 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 14:25:06 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef enum e_expand_state			t_expand_state;
typedef struct s_expand_handlers	t_expand_handlers;

enum	e_expand_state
{
	E_S_IN_WORD = 1,
	E_S_IN_SINGLE_QUOTE,
	E_S_IN_DOUBLE_QUOTE,
	E_S_IN_VAR,
	E_S_FINISHED
};

struct	s_expand_handlers
{
	t_expand_state	state;
	t_expand_state	(*handler)(char *, int);
};

char	*expand(char *str);

#endif

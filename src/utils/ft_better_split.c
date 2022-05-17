/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:19:48 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/17 13:44:23 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>

typedef struct s_split_params
{
	char		**tab;
	size_t		nb_str;
	size_t		i;
	int			k;
	int			iq;
}				t_split_params;

static size_t	ft_nb_slot(char *str, char c)
{
	size_t	nb_str;
	size_t	k;
	int		inside_quote;

	inside_quote = -1;
	k = 0;
	nb_str = 0;
	while (*str)
	{
		if (*str == 39)
			inside_quote *= -1;
		if (*str != c && k == 0)
		{
			k = 1;
			nb_str++;
		}
		else if (*str == c && inside_quote == -1)
			k = 0;
		str++;
	}
	return (nb_str);
}

t_split_params	ft_init_params(void)
{
	t_split_params	sp;

	sp.iq = -1;
	sp.i = -1;
	sp.nb_str = 0;
	sp.k = -1;
	return (sp);
}

char	**ft_better_split(char *s, char c)
{
	t_split_params	sp;

	sp = ft_init_params();
	if (s == NULL)
		return (NULL);
	sp.tab = malloc(sizeof(char *) * (ft_nb_slot(s, c) + 1));
	if (sp.tab == NULL)
		return (NULL);
	while (++sp.i <= ft_strlen(s))
	{
		if (s[sp.i] == 39)
			sp.iq *= -1;
		if (s[sp.i] != c && sp.k == -1)
			sp.k = sp.i;
		else if (((s[sp.i] == c && sp.iq == -1) || sp.i == ft_strlen(s))
			&& sp.k != -1)
		{
			sp.tab[sp.nb_str++] = ft_strtrim(ft_strncpy(s, sp.k, sp.i), "'");
			sp.k = -1;
		}
	}
	sp.tab[sp.nb_str] = 0;
	return (sp.tab);
}

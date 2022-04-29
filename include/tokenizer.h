/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:43:39 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/29 17:48:57 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <minishell.h>
# include <libft.h>

typedef struct s_quote	t_quote;

struct s_quote {
	t_token_type	type;
	int				n;
};

t_list	*add_token(t_token_type type, t_token_data data, t_list *tokens);
void	add_metacharacter(char *c, t_list **tokens);
void	add_word(char *word, t_list **tokens);
void	end_quote(char *quote, t_quote *quotes);
void	start_quote(char *quote, t_quote *quotes, t_list **tokens);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:55:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/09 16:26:59 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <tokenizer.h>
# include <libft.h>

typedef enum e_parser_state	t_parser_state;
typedef struct s_parser		t_parser;
typedef struct s_cmd		t_cmd;

enum e_parser_state
{
	P_S_WORKING = 1,
	P_S_ERROR,
	P_S_FINISHED
};

struct s_parser
{
	t_list			*cmds;
	t_parser_state	state;
	void			(*destructor)(t_parser *);
};

struct s_cmd
{
	char	*cmd;
	t_list	*in;
	t_list	*out;
	int		piped;
	void	(*destructor)(t_cmd *);
};

t_cmd	*cmd_constructor(void);

void	parser_word_handler(t_parser *p, t_token *t);
void	parser_pipe_handler(t_parser *p, t_token *t);
void	parser_heredoc_handler(t_parser *p, t_token *t);
void	parser_redirection_in_handler(t_parser *p, t_token *t);
void	parser_redirection_out_handler(t_parser *p, t_token *t);
void	parser_redirection_append_handler(t_parser *p, t_token *t);
void	parser_redirection_error_handler(t_parser *p, t_token *t);

#endif

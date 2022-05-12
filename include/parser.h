/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:55:37 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/12 15:03:57 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <tokenizer.h>
# include <libft.h>

typedef enum e_parser_state				t_parser_state;
typedef enum e_redir_type				t_redir_type;
typedef struct s_parser					t_parser;
typedef struct s_cmd					t_cmd;
typedef struct s_parser_token_handlers	t_parser_token_handlers;
typedef struct s_redir					t_redir;

enum e_parser_state
{
	P_S_WORKING = 1,
	P_S_ERROR,
	P_S_FINISHED
};

enum e_redir_type
{
	P_RT_IN = 1,
	P_RT_OUT,
	P_RT_HEREDOC,
	P_RT_HEREDOC_UNQUOTED,
	P_RT_APPEND
};

struct s_parser
{
	t_list			*cmds;
	t_cmd			*curr_cmd;
	t_token_type	last_token_type;
	t_parser_state	state;
	t_list			*tokens;
	void			(*destructor)(t_parser *);
};

struct s_redir
{
	t_redir_type	type;
	char			*target;
};

struct s_cmd
{
	char	*cmd;
	t_list	*in;
	t_list	*out;
	int		piped;
	void	(*destructor)(t_cmd *);
};

struct s_parser_token_handlers
{
	t_token_type	token_type;
	void			(*handler)(t_parser *);
};

t_cmd	*cmd_constructor(void);

void	parser_word_handler(t_parser *p);
void	parser_pipe_handler(t_parser *p);
void	parser_heredoc_handler(t_parser *p);
void	parser_redirection_in_handler(t_parser *p);
void	parser_redirection_out_handler(t_parser *p);
void	parser_redirection_append_handler(t_parser *p);

void	parser_add_to_cmd(t_parser *p);
void	parser_new_cmd(t_parser *p);
void	parser_end_cmd(t_parser	*p);
void	parser_pipe_cmd(t_parser *p);
void	parser_new_redir(t_parser *p);
void	parser_set_redir(t_parser *p);
void	parser_syntax_error(t_parser *p);

void	parser_end(t_parser *p);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 11:56:51 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_tokenizer_state				t_tokenizer_state;
typedef enum e_tokenizer_char_type			t_tokenizer_char_type;
typedef enum e_toke_type					t_token_type;
typedef struct s_tokenizer					t_tokenizer;
typedef struct s_tokenizer_char_handlers	t_tokenizer_char_handlers;
typedef struct s_token						t_token;

enum e_tokenizer_state
{
	T_S_WORKING = 1,
	T_S_FINISHED
};

enum e_tokenizer_char_type
{
	T_CT_CHAR = 1,
	T_CT_SINGLE_QUOTE,
	T_CT_DOUBLE_QUOTE,
	T_CT_PIPE,
	T_CT_LESS,
	T_CT_GREAT,
	T_CT_WHITESPACE,
	T_CT_UNIMPLEMENTED,
	T_CT_END
};

enum e_toke_type
{
	T_TT_WORD = 1,
	T_TT_PIPE,
	T_TT_HEREDOC,
	T_TT_REDIRECTION_IN,
	T_TT_REDIRECTION_OUT,
	T_TT_REDIRECTION_APPEND,
	T_TT_SINGLE_QUOTE_WORD,
	T_TT_DOUBLE_QUOTE_WORD,
	T_TT_SYNTAX_ERROR,
	T_TT_UNIMPLEMENTED,
	T_TT_NONE
};

struct s_tokenizer
{
	t_list					*tokens;
	char					*line;
	int						cursor;
	t_token					*curr_token;
	t_tokenizer_state		state;
	void					(*free)(t_tokenizer **);
};

struct s_token {
	char			*str;
	t_token_type	type;
	void			(*free)(t_token **);
};

struct s_tokenizer_char_handlers
{
	t_tokenizer_char_type	char_type;
	void					(*handler)(t_tokenizer *);
};

void		tokenizer_char_handler(t_tokenizer *t);
void		tokenizer_double_quote_handler(t_tokenizer *t);
void		tokenizer_end_handler(t_tokenizer *t);
void		tokenizer_great_handler(t_tokenizer *t);
void		tokenizer_less_handler(t_tokenizer *t);
void		tokenizer_pipe_handler(t_tokenizer *t);
void		tokenizer_single_quote_handler(t_tokenizer *t);
void		tokenizer_unimplemented_handler(t_tokenizer *t);
void		tokenizer_whitespace_handler(t_tokenizer *t);

void		tokenizer_new_token(t_tokenizer *t, t_token_type type);
void		tokenizer_delimit_curr_token(t_tokenizer *t);
void		tokenizer_delimit_and_new(t_tokenizer *t, t_token_type type);

t_token		*token_constructor(t_token_type type, char *token);

#endif

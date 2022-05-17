/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:46:57 by seb               #+#    #+#             */
/*   Updated: 2022/05/17 14:04:25 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

typedef enum e_tokenizer_state				t_tokenizer_state;
typedef enum e_toke_type					t_token_type;
typedef struct s_tokenizer					t_tokenizer;
typedef struct s_tokenizer_char_handlers	t_tokenizer_char_handlers;
typedef struct s_token						t_token;

enum e_tokenizer_state
{
	T_S_WORKING = 1,
	T_S_ERROR,
	T_S_FINISHED
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
	T_TT_SYNTAX_ERROR
};

struct s_tokenizer
{
	t_list					*tokens;
	char					*line;
	int						cursor;
	t_token					*curr_token;
	t_tokenizer_state		state;
	void					(*destructor)(t_tokenizer *);
};

struct s_token {
	char			*str;
	t_token_type	type;
	void			(*destructor)(t_token *);
};

struct s_tokenizer_char_handlers
{
	t_token_type	char_type;
	void			(*handler)(t_tokenizer *, t_token_type);
	t_token_type	arg_type;
};

void		tokenizer_char_handler(t_tokenizer *t);
void		tokenizer_double_quote_handler(t_tokenizer *t);
void		tokenizer_end_handler(t_tokenizer *t);
void		tokenizer_great_handler(t_tokenizer *t);
void		tokenizer_less_handler(t_tokenizer *t);
void		tokenizer_pipe_handler(t_tokenizer *t);
void		tokenizer_single_quote_handler(t_tokenizer *t);
void		tokenizer_whitespace_handler(t_tokenizer *t);

/* Put curr_token at the end of the tokens list.*/
void		tokenizer_delimit_curr_token(t_tokenizer *t);
/* Put the curr_token at the end of the tokens list, create a new one,
and move the cursor forward in the tokenized string.*/
void		tokenizer_delimit_new(t_tokenizer *t, t_token_type type);
/* Put the curr_token at the end tokens list as well as a syntax error token.*/
void		tokenizer_error_token(t_tokenizer *t, t_token_type type);
/* Move the cursor forward in the tokenized string.*/
void		tokenizer_increase_cursor(t_tokenizer *t, t_token_type type);
/* Create a new curr_token, and move the cursor forward in the tokenized
string.*/
void		tokenizer_new_token(t_tokenizer *t, t_token_type type);

t_token		*token_constructor(t_token_type type, char *token);
t_tokenizer	*tokenize(char *line);

#endif

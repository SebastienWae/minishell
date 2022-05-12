/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:57:33 by seb               #+#    #+#             */
/*   Updated: 2022/05/10 17:11:08 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <tokenizer.h>
# include <parser.h>

/* Print t_token struct in the STDIN. */
void	print_token(t_token *token);
/* Print t_tokenizer struct in the STDIN. */
void	print_tokenizer(t_tokenizer *tokenizer);
/* Print t_parser struct in the STDIN. */
void	print_parser(t_parser *parser);
/* Print t_cmd struct in the STDIN. */
void	print_cmd(t_cmd *cmd);
/* Print t_redir struct in the STDIN. */
void	print_redir(t_redir *redir);

#endif

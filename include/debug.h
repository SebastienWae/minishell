/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:57:33 by seb               #+#    #+#             */
/*   Updated: 2022/05/07 21:59:11 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <tokenizer.h>

/* Print t_token struct in the STDIN. */
void	print_token(t_token *token);
/* Print t_tokenizer struct in the STDIN. */
void	print_tokenizer(t_tokenizer *tokenizer);

#endif

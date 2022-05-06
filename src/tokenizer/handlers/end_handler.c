/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:53:30 by seb               #+#    #+#             */
/*   Updated: 2022/05/06 10:51:12 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	tokenizer_end_handler(t_tokenizer *t)
{
	if (t->curr_token)
		tokenizer_delimit_curr_token(t);
	t->state = T_S_FINISHED;
}

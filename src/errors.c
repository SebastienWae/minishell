/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:50 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/28 14:55:51 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_arg_error(int argc)
{
	if (argc != 1)
	{
		write (2, "Minishell does not take arguments\n", 34);
		exit (0);
	}
}

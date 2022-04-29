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

#include <unistd.h>
#include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

void ft_check_arg_error(argc)
{
	if (argc != 1)
	{
		write (2, "minishell does not take any argument\n", 37);
		exit (0);
	}
}
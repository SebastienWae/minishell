/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:07:03 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/03 15:07:05 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sig_handler.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_sig(void)
{
	if (signal(SIGINT, &ft_sig_handler) == SIG_ERR)
	{
		write(2, "Cannot catch signal. Abort\n", 27);
		exit(1);
	}
	if (signal(SIGQUIT, &ft_sig_handler) == SIG_ERR)
	{
		write(2, "Cannot catch signal. Abort\n", 27);
		exit(1);
	}
}

int	ft_ctrl_d_handler(char *str)
{
	if (str == NULL)
	{
		printf("\033[2D");
		printf("\033[1A");
		printf("\033[10C");
		printf("exit\n");
		exit(0);
	}
	else
		return (1);
}

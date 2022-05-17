/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:07:03 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/17 13:43:53 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>

/* Redirection of Ctrl C => newline and Ctrl \ => does nothing */
void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
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

/* Checks signal error at launch */
void	ft_sig(void)
{
	if (signal(SIGINT, &ft_sig_handler) == SIG_ERR || signal(SIGQUIT,
			&ft_sig_handler) == SIG_ERR)
	{
		write(2, "Cannot catch signal. Abort\n", 27);
		exit(1);
	}
}

/* Ctrl D exits if nothing is written in prompt, else does nothing */
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

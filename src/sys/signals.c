/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:07:03 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/18 13:21:14 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#if __linux__
# include <signal.h>
#endif

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
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": Cannot catch signal. Aborting\n", 2);
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

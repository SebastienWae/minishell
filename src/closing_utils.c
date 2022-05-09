/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:55:48 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/05 17:55:52 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <close_functions.h>

void ft_close_fd(t_minishell shell, int fd_in, int fd_out)
{
		
	dup2 (shell.saved_stdout, 1);
    dup2 (shell.saved_stdin, 0);
    close(fd_out);			
    close(fd_in);
}

void    ft_close_saved_fd (t_minishell shell)
{
    close(shell.saved_stdout);
	close(shell.saved_stdin);
}

void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i ++;
	}
	free(tab);
}

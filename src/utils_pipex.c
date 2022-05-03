/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:12:22 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/12 14:17:31 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void	ft_error_exit(t_pipex cmd)
{
	ft_putstr_fd(strerror(errno), 2);
	free(cmd.path);
	exit (1);
}

void	ft_error_exit_arg(void)
{
	ft_putstr_fd(strerror(errno), 2);
	exit (1);
}

//enlever messages erreur inutiles
void	ft_nb_arg_error(int argc)
{
	if (argc != 5)
	{
		write(2, "\n### Error ###\n\nPlease use format : \
		./pipex inputfile cmd1 cmd2 outputfile\n\n", 76);
		exit (1);
	}
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

void	ft_free_all(t_pipex cmd, int choice)
{
	if (choice == 1)
	{
		free(cmd.main1);
		ft_free_char_tab(cmd.arg1);
		ft_free_char_tab(cmd.path);
		return ;
	}
	if (choice == 2)
	{
		free(cmd.main2);
		ft_free_char_tab(cmd.arg2);
		ft_free_char_tab(cmd.path);
		return ;
	}
	if (cmd.input_file != -1)
	{
		free(cmd.main1);
		free(cmd.main2);
		ft_free_char_tab(cmd.arg2);
		ft_free_char_tab(cmd.arg1);
	}		
	ft_free_char_tab(cmd.path);
}

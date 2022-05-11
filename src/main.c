/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:41:02 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/29 17:41:04 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <sys_call.h>
#include <sig_handler.h>
#include <built_in_functions.h>
#include <init.h>
#include <close.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	t_minishell		shell;
	char			*str;
	t_fd_in_out		fd;

	shell = ft_init_all(argc, argv, env); // init env, config, sig, save default stdin and out 
	while (1)
	{
		str = readline("Minishell>");
		if (ft_ctrl_d_handler(str))
		{
			add_history(str);
			//ajouter ici appel fonction seb		
			fd = ft_init_fd_minishell(); // a modifier pour mettre les fd de la cmd
			if (str[0] == '@') //test provisoire heredoc
				ft_heredoc_in("cat -e", shell, env);
			else
				if (str[0] != 0)
				{			
					if (ft_strcmp(str, "pipe") == 0) // test provisoire pipe
						shell = ft_pipe(shell, env); // remplacer avec appel sur liste de cmd
					else // une seule commande
						shell = ft_launch_cmd(str, shell, env);	// remplacer par commande
				}
			ft_close_fd(shell, fd.in, fd.out); //restaure les stdin et out par defaut pour le rendre a readline
		}
		free (str);	
	}
	ft_close_saved_fd(shell);	
	ft_lstclear(&shell.local_env, free);
	return (0);
}

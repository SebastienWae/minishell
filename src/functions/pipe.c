/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/05 11:56:41 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_next_process(pid_t process, int fd_tab[2])
{
	waitpid(process, NULL, 0);	
	close(fd_tab[1]);						
	dup2 (fd_tab[0], STDIN_FILENO);		
}

t_minishell	ft_pipe(t_minishell shell, char **env)
{
	char	**buffer;

	buffer = malloc(sizeof(char *) * 5);
	buffer[0] = "cat f1";	
	buffer[1] = "grep blou";
	buffer[2] = "tr 'o' 'n'";
	buffer[3] = "tr 'n' '@'";
	buffer[4] = 0;
	int	i;
	int fd_tab[2];
	pid_t process;

	i = -1;
	while (buffer[++i] != 0)
	{										
		if (pipe(fd_tab) == -1)
		{
			write (2, "Pipe creation failed\n", 21);
			return (shell);
		}				
		process = fork();	
		if (process == -1)
		{
			write (2, "Process creation failed\n", 24);
			return (shell);
		}	
		if (process == 0)
		{				
			close(fd_tab[0]);
			if(buffer[i + 1] != NULL)									
				dup2(fd_tab[1], STDOUT_FILENO);															
			shell = ft_launch_cmd(buffer[i], shell, env);							
			exit(0);
		}
		else
			ft_next_process(process, fd_tab);							
	}	
	return (shell);
}				
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 15:55:26 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <functions.h>
#include <sys.h>
#include <utils.h>

char	**ft_better_split(char *s, char c);

int	ft_next_process(pid_t process, int fd_tab[2])
{
	int status;

	waitpid(process, &status, 0);
	close(fd_tab[1]);
	dup2 (fd_tab[0], STDIN_FILENO);
	g_out = WEXITSTATUS(status);
	return (g_out);
}

t_minishell	ft_launch_cmd(char *str, t_minishell shell, char **env)
{
	char	**parsed_str;

	parsed_str = ft_better_split(str, ' '); // a remplacer ou enlever selon le retour de seb
	if (ft_strcmp(parsed_str[0], "exit") == 0)
		ft_exit(parsed_str, shell);
	else if (ft_is_builtin_cmd(parsed_str[0]))
		shell.local_env = ft_execute_builtin_cmd(parsed_str, shell.local_env);
	else
		g_out = ft_sys_cmd_process(parsed_str, str, env);
	free (parsed_str);
	return (shell);
}

t_minishell	ft_pipe(t_minishell shell, char **env)
{
	char	**buffer;
	int		i;
	int		fd_tab[2];
	pid_t	process;

	buffer = malloc(sizeof(char *) * 5);
	buffer[0] = "cat f1";
	buffer[1] = "grep blou";
	buffer[2] = "tr 'o' 'n'";
	buffer[3] = "tr 'n' '@'";
	buffer[4] = 0;
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
			if (buffer[i + 1])
				dup2(fd_tab[1], STDOUT_FILENO);
			shell = ft_launch_cmd(buffer[i], shell, env);
			exit(g_out);
		}
		else
			g_out = ft_next_process(process, fd_tab);
	}	
	return (shell);
}

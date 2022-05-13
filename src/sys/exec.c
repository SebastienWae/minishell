/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:46:29 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/13 14:57:57 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <functions.h>
#include <sys.h>
#include <sys/wait.h>
#include <utils.h>

int	ft_next_process(pid_t process, int fd_tab[2])
{
	int	status;

	waitpid(process, &status, 0);
	close(fd_tab[1]);
	dup2 (fd_tab[0], STDIN_FILENO);
	g_out = WEXITSTATUS(status);
	return (g_out);
}

void	ft_launch_cmd(char *str, t_minishell shell)
{
	char	**parsed_str;

	parsed_str = ft_split(str, ' ');
	if (ft_strcmp(parsed_str[0], "exit") == 0)
		ft_exit(parsed_str, shell);
	else if (ft_is_builtin_cmd(parsed_str[0]))
		shell.local_env = ft_execute_builtin_cmd(parsed_str,
				shell.local_env);
	else
		g_out = ft_sys_cmd_process(parsed_str, str, shell.local_env);
	free (parsed_str);
}

t_minishell	ft_pipe(t_minishell shell, t_list *cmd)
{	
	int			fd_tab[2];
	pid_t		process;

	while (cmd != 0)
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
			if (cmd->next)
				dup2(fd_tab[1], STDOUT_FILENO);
			ft_launch_cmd(((t_cmd *)(cmd->content))->cmd, shell);
			exit(g_out);
		}
		else
			g_out = ft_next_process(process, fd_tab);
		cmd = cmd->next;
	}	
	return (shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:16:34 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/13 16:40:01 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <utils.h>
#include <sys/fcntl.h>
#include <utils.h>
#include <fcntl.h>
#include <sys.h>

void	ft_close_fd(t_minishell shell, int fd_in, int fd_out)
{
	dup2(shell.saved_stdout, 1);
	dup2(shell.saved_stdin, 0);
	close(fd_out);
	close(fd_in);
}

void	ft_close_saved_fd(t_minishell shell)
{
	close(shell.saved_stdout);
	close(shell.saved_stdin);
}

//pas mal
void	ft_heredoc_in(char *cmd, t_minishell shell, char **env)
{
	char	*input;
	char	*line;
	int		fd_tmp;

	(void) env; // A ENLEVER
	input = "";
	line = get_next_line(STDIN_FILENO);
	while (1)
	{
		input = ft_strjoin(input, line);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, "EOF\n") == 0) // changer par delimiteur
			break ;
	}
	fd_tmp = open("fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd_tmp, input, ft_strlen(input));
	//dup2(fd_tmp, STDIN_FILENO);
	ft_launch_cmd(ft_strjoin(cmd, " fd_tmp"), shell);
	unlink("fd_tmp");
	close(fd_tmp);
}

static int	redir_in(t_redir *redir)
{
	static char	*redir_types[] = {"NONE", "IN", "OUT", "HEREDOC", "APPEND"};
	int fd;

	/*printf("	    - type: %s\n", redir_types[redir->type]);
	printf("	    - target: %s\n", redir->target);*/	
	if (ft_strcmp(redir_types[redir->type], "IN") == 0)
		fd = open(redir->target, O_RDONLY);
	else if (ft_strcmp(redir_types[redir->type], "HEREDOC") == 0)
		fd = dup(0);
	else 
		fd = dup(0);
	return (fd);
}
static int	redir_out(t_redir *redir)
{
	static char	*redir_types[] = {"NONE", "IN", "OUT", "HEREDOC", "APPEND"};
	int	fd;
	
	/*printf("	    - type: %s\n", redir_types[redir->type]);
	printf("	    - target: %s\n", redir->target);*/
	if (ft_strcmp(redir_types[redir->type], "OUT") == 0)
		fd = open(redir->target, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(redir_types[redir->type], "APPEND") == 0)
		fd = open(redir->target, O_RDWR | O_CREAT | O_APPEND, 0644);
	else 
		fd = dup(1);
	return (fd);
}

t_fd_in_out	ft_fd_manager(t_cmd *cmd)// faire passer les fd in et out depuis struct de seb
{
	t_fd_in_out		fd;
	int	fd_tmp;
	
	t_list	*in;
	t_list	*out;

	in = cmd->in;
	out = cmd->out;	
	while (in)
	{		
		fd_tmp = redir_in(in->content);
		fd.in = dup(fd_tmp);
		if (in->next)
			close(fd.in);
		close(fd_tmp);
		in = in->next;
	}
	dup2(fd.in, STDIN_FILENO);	
	while (out)
	{		
		fd_tmp = redir_out(out->content);
		fd.out = dup(fd_tmp);
		if (out->next)
			close(fd.out);
		close(fd_tmp);
		out = out->next;
	}
	dup2(fd.out, STDOUT_FILENO);
	return (fd);
}

t_fd_in_out	ft_init_fd(void)// faire passer les fd in et out depuis struct de seb
{
	t_fd_in_out		fd;


	fd.out = dup(1);
	fd.in = dup(0);
	return (fd);
}

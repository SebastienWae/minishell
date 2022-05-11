/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:16:34 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/05 17:16:36 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <init.h>
#include <stdio.h>
#include <get_next_line.h>

//pas mal
void   ft_heredoc_in(char *cmd, t_minishell shell, char **env)
{
        char *input;
        char *line;

    
        input = "";  
        line = get_next_line(STDIN_FILENO);   
        while (1)
        {
            input = ft_strjoin(input, line);
            line = get_next_line(STDIN_FILENO);
            if (ft_strcmp(line, "EOF\n") == 0) // changer par delimiteur
                break;                      
        }
        int fd_tmp = open("fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
        write(fd_tmp, input, ft_strlen(input));         
        //dup2(fd_tmp, STDIN_FILENO);
        shell = ft_launch_cmd(ft_strjoin(cmd, " fd_tmp"), shell, env);
        unlink("fd_tmp");
        close(fd_tmp);

}

t_fd_in_out ft_init_fd_minishell(void)// faire passer les fd in et out depuis struct de seb
{
	t_fd_in_out		fd;
    
    // par defaut
    fd.out = dup(1); 
    fd.in = dup(0); 
    
    /* tout ce bloc pour mettre un file in ou file out 
    fd.out = open("f2", O_RDWR | O_CREAT | O_TRUNC, 0777); //ajouter les bons flags selon > ou >>
    fd.in = open("f1", O_RDONLY);
    dup2(fd.out, STDOUT_FILENO);
    dup2(fd.in, STDIN_FILENO);
    */
    return (fd);
}


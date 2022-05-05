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
#include <init_functions.h>

t_fd_in_out ft_init_fd_minishell(void)// faire passer les fd in et out depuis struct de seb
{
	t_fd_in_out		fd;
    
    fd.out = dup(1);
    fd.in = dup(0);
   /* fd.out = open("f2", O_RDWR | O_CREAT | O_TRUNC, 0777); //ajouter les bons flags selon > ou >>
    fd.in = open("f1", O_RDONLY);*/
    dup2(fd.out, STDOUT_FILENO);	
    dup2(fd.in, STDIN_FILENO); 
    return (fd);
}


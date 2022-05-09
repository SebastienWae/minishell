/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:56:31 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/05 17:56:36 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_FUNCTIONS_H
# define CLOSE_FUNCTIONS_H

# include <minishell.h>

void 	ft_close_fd(t_minishell shell, int fd_in, int fd_out);
void    ft_close_saved_fd (t_minishell shell);
void	ft_free_char_tab(char **tab);

#endif




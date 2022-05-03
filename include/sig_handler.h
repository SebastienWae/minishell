/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:58:52 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/03 15:58:53 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H
# include <libft.h>
int		ft_ctrl_d_handler(char *str);
void	ft_sig(void);
void	ft_sig_handler(int sig);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:41:46 by jeulliot          #+#    #+#             */
/*   Updated: 2022/03/03 13:41:49 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 10000

char	*get_next_line(int fd);
char	*ft_charge_buffer(int fd, char *buf, char *tmp, char *next);
int		ft_is_a_line(char *s);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcat(char *dest, char *s1, char *s2);
char	*ft_fill_line(char *tmp);
char	*ft_copy_temp(char *str);

#endif
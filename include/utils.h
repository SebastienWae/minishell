/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:57:31 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 15:43:46 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define BUFFER_SIZE 1000

# include <unistd.h>

int		is_whitespace(char c);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strncpy(char *src, size_t index, size_t end);

char	*ft_copy_temp(char *str);
char	*ft_fill_line(char *tmp);
char	*get_next_line(int fd);
char	*ft_strcat(char *dest, char *s1, char *s2);
int		ft_is_a_line(char *s);
char	*ft_charge_buffer(int fd, char *buf, char *tmp, char *next);

#endif

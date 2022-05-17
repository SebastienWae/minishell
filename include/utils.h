/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:57:31 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/17 15:05:09 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define BUFFER_SIZE 1000

# include <unistd.h>

typedef struct s_array	t_array;

struct s_array
{
	size_t	len;
	char	**values;
	void	(*destroy)(t_array *);
};

int		is_whitespace(char c);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strncpy(char *src, size_t index, size_t end);
char	*ft_strappend(const char *s1, const char c);
char	*ft_strjoin_sep(const char *s1, const char *s2, const char *sep);

char	*ft_copy_temp(char *str);
char	*ft_fill_line(char *tmp);
char	*get_next_line(int fd);
char	*ft_strcat(char *dest, char *s1, char *s2);
int		ft_is_a_line(char *s);
char	*ft_charge_buffer(int fd, char *buf, char *tmp, char *next);

t_array	*array_constructor(void);
void	array_push(t_array *arr, char *str);
void	array_print(t_array *arr);

#endif

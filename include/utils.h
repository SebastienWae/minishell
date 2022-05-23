/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:57:31 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/23 12:35:57 by seb              ###   ########.fr       */
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

char	*get_next_line(int fd);
char	*get_first_line(char **s);

t_array	*array_constructor(void);
void	array_push(t_array *arr, char *str);
void	array_remove(t_array **arr, size_t i);
void	array_print(t_array *arr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:48:00 by swaegene          #+#    #+#             */
/*   Updated: 2022/04/28 16:22:02 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "pipex.h"

typedef struct s_cmd	t_cmd;
typedef struct s_in		t_in;
typedef struct s_out	t_out;

enum	e_in_type {
	IN_PIPE,
	IN_FILE,
	HEREDOC
};
enum	e_out_type {
	OUT_PIPE,
	OUT_FILE,
	OUT_FILE_APPEND,
	STD,
};

union u_in_data {
	t_cmd	*pipe_src;
	char	*path;
};

struct s_cmd {
	char	**cmd;
	t_list	*in;
	t_out	*out;
};
struct s_in {
	enum e_in_type	type;
	union u_in_data	data;
};
struct s_out {
	enum e_out_type	type;
};


typedef struct s_split_params
{
	char	**tab;
	size_t	nb_str;
	size_t	i;
	int		k;
	int		iq;
}	t_split_params;

typedef struct	s_local_env t_local_env;

struct	s_local_env
{
	char *name;
	char *content;
	t_local_env *next;
}	;


char	**ft_better_split(char *s, char c);
//size_t	ft_strlen(char *str);
//char	*ft_strtrim(char *s1, char *set);
int		ft_strcmp(char *str1, char *str2);
int		ft_execute_sys_cmd(char **cmd, char **env);
int 	ft_is_builtin_cmd(char *str);
void	ft_check_arg_error(int argc);
int		ft_pwd(char **cmd);
int		ft_echo(char **cmd);
int		ft_cd(char **cmd);
int		ft_unset(char **cmd, t_list **local_env);
int		ft_export(char **cmd,t_list **local_env);
int		ft_execute_builtin_cmd(char **parsed_str,t_list **local_env);

#endif

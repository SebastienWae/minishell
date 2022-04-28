#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_split_params
{
	char	**tab;
	size_t	nb_str;
	size_t	i;
	int		k;
	int		iq;
}	t_split_params;

char	**ft_better_split(char *s, char c);
size_t	ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
int		ft_strcmp(char *str1, char *str2);
int		ft_execute_sys_cmd(char **cmd, char **env);
int 	ft_is_builtin_cmd(char *str);
void	ft_check_arg_error(int argc);
int		ft_pwd(char **cmd);
int		ft_echo(char **cmd);
int		ft_cd(char **cmd);
int		ft_unset(char **cmd);
int		ft_export(char **cmd);
int		ft_execute_builtin_cmd(char **parsed_str);
#endif
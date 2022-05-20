/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:08:07 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/19 14:29:50 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>
#include <libft.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

static int	ft_cd_error(char *dir)
{
	if (chdir(dir) == -1)
	{
		g_out = 1;
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": cd : ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

t_list	*ft_new_dir(t_list *local_env)
{
	char	*new_dir;

	free(local_env->content);
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
		local_env->content = ft_strjoin("PWD=", "ERROR");
	else
	{
		local_env->content = ft_strjoin("PWD=", new_dir);
		free(new_dir);
	}
	return (local_env);
}

void	ft_cd(char **cmd, t_list *local_env)
{
	char	*old_dir;
	char	*new_dir;

	g_out = 0;
	old_dir = ft_get_env_var_value(local_env, "PWD");
	if (cmd[1] == 0)
		chdir(getenv("HOME"));
	else if (ft_cd_error(cmd[1]))
		return ;
	while (local_env)
	{
		if (!ft_strncmp("PWD=", local_env->content, 4))
			local_env = ft_new_dir(local_env);
		if (!ft_strncmp("OLDPWD=", local_env->content, 7))
		{
			free(local_env->content);
			local_env->content = ft_strjoin("OLDPWD=", old_dir);
		}
		local_env = local_env->next;
	}
	free(old_dir);
}

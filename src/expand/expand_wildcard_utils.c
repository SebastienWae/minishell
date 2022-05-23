/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:31:18 by seb               #+#    #+#             */
/*   Updated: 2022/05/23 15:07:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <dirent.h>
#include <expand.h>
#include <stdlib.h>

int	wild_is_present(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] == -1)
		{
			w++;
			str[i] = '*';
		}
		i++;
	}
	return (w);
}

static int	get_n_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				file_count;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	if (!dir)
		return (0);
	file_count = 0;
	entry = readdir(dir);
	if (entry)
		file_count = 1;
	while (entry)
	{
		file_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	free(cwd);
	return (file_count);
}

char	**get_files_name(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i[2];
	char			*cwd;

	i[0] = get_n_files();
	cwd = getcwd(NULL, 0);
	files = ft_calloc(sizeof(char *), i[0] + 1);
	if (!files)
		return (NULL);
	dir = opendir(cwd);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	i[1] = 0;
	while (entry)
	{
		files[i[1]] = ft_strdup(entry->d_name);
		i[1]++;
		entry = readdir(dir);
	}
	closedir(dir);
	free(cwd);
	return (files);
}

void	free_file_names(char **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		free(files[i]);
		i++;
	}
	free(files);
}

int	wild_check_glob(char *expr, char *file)
{
	if (file[0] == '.')
	{
		if (expr[0] != '.')
			return (0);
	}
	return (1);
}

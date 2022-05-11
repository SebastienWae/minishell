/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:48 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/11 15:45:01 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free (current_dir);
	g_out = 0;
}

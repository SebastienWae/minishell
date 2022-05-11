/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:20:21 by jeulliot          #+#    #+#             */
/*   Updated: 2022/05/11 11:20:29 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_CALL_H
# define SYS_CALL_H

/* Path building, access checking, command launching */
int		ft_sys_cmd_process(char **parsed_str, char *str, char **env);
int		*ft_execute_sys_cmd(char **cmd, char **env);
char	*ft_search_path(char **env);
char	*ft_build_cmd(char **path, char *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:35:12 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/02 16:37:42 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_builtin(char *cmd)
{
	int				max_len;
	size_t			i;
	const size_t	cmd_len = ft_strlen(cmd);
	const char		*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit",
	};

	i = 0;
	while (builtins[i])
	{
		max_len = ft_max(cmd_len, ft_strlen(builtins[i]));
		if (ft_strncmp(cmd, (char *)builtins[i], max_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_data *data, t_cmds *cmd, char *cmd_name)
{
	int	retval;

	retval = 0;
	if (ft_strncmp(cmd_name, "echo", 4) == 0)
		retval = ft_echo(data, cmd);
	else if (ft_strncmp(cmd_name, "cd", 2) == 0)
		retval = ft_cd(data, cmd);
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		retval = ft_pwd(data, cmd);
	else if (ft_strncmp(cmd_name, "export", 6) == 0)
		retval = ft_export(data, cmd);
	else if (ft_strncmp(cmd_name, "unset", 5) == 0)
		retval = ft_unset(data, cmd);
	else if (ft_strncmp(cmd_name, "env", 3) == 0)
		retval = ft_env(data, cmd);
	else if (ft_strncmp(cmd_name, "exit", 4) == 0)
		retval = ft_exit(data, cmd);
	return (retval);
}

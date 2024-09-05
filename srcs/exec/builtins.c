/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:35:12 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/05 16:13:11 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_builtin(char *cmd)
{
	size_t			max_len;
	size_t			i;
	size_t			cmd_len;
	const char		*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (i < 7)
	{
		max_len = ft_max(cmd_len, ft_strlen(builtins[i]));
		if (ft_strncmp(cmd, (char *)builtins[i], max_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_data *data, char **cmdve)
{
	int	retval;

	retval = 0;
	if (ft_strncmp(cmdve[0], "echo", 4) == 0)
		retval = ft_echo(data, cmdve);
	else if (ft_strncmp(cmdve[0], "cd", 2) == 0)
		retval = ft_cd(data, cmdve);
	else if (ft_strncmp(cmdve[0], "pwd", 3) == 0)
		retval = ft_pwd(data, cmdve);
	else if (ft_strncmp(cmdve[0], "export", 6) == 0)
		retval = ft_export(data, cmdve);
	else if (ft_strncmp(cmdve[0], "unset", 5) == 0)
		retval = ft_unset(data, cmdve);
	else if (ft_strncmp(cmdve[0], "env", 3) == 0)
		retval = ft_env(data, cmdve);
	else if (ft_strncmp(cmdve[0], "exit", 4) == 0)
		retval = ft_exit(data, cmdve);
	return (retval);
}

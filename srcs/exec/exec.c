/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/08/30 16:42:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

static int	is_builtin(char *cmd)
{
	int				max_len;
	size_t			i;
	const size_t	cmd_len = ft_strlen(cmd);
	const char		*builtins = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit",
	};

	i = 0;
	while (builtins[i])
	{
		max_len = ft_max(cmd_len, ft_strlen(builtins[i]));
		if (ft_strncmp(cmd, builtins[i], max_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	exec_builtin(t_cmds *cmd, char *cmd_name)
{
	int	retval;

	if (ft_strncmp(cmd_name, "echo", 4) == 0)
		retval = ft_echo(cmd);
	else if (ft_strncmp(cmd_name, "cd", 2) == 0)
		retval = ft_cd(cmd);
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		retval = ft_pwd(cmd);
	else if (ft_strncmp(cmd_name, "export", 6) == 0)
		retval = ft_export(cmd);
	else if (ft_strncmp(cmd_name, "unset", 5) == 0)
		retval = ft_unset(cmd);
	else if (ft_strncmp(cmd_name, "env", 3) == 0)
		retval = ft_env(cmd);
	else if (ft_strncmp(cmd_name, "exit", 4) == 0)
		retval = ft_exit(cmd);
	return (retval);
}

int	exec(t_cmds *cmd)
{
	t_tokens	*tokens;

	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			if (is_builtin(tokens->str))
			{
				if (exec_builtin(cmd, tokens->str))
					return (1);
			}
			else
				// exec from path
			break ;
		}
		tokens = tokens->next;
	}
	return (0);
}

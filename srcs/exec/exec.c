/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/04 12:17:57 by mtrullar         ###   ########.fr       */
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

static int	exec_builtin(t_data *data, t_cmds *cmd, char *cmd_name)
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

static char	***ft_make_cmdve(t_cmds *cmd)
{
	char		***cmdve;
	t_tokens	*tokens;
	int			n_cmds;

	tokens = cmd->tokens;
	n_cmds = 0;
	while (tokens)
	{
		if (tokens->type == CMD)
			n_cmds++;
		tokens = tokens->next;
	}
	if (n_cmds == 0)
		return (NULL);
	cmdve = malloc(sizeof(char *) * (n_cmds + 1));
	if (!cmdve)
		return (NULL);
	return (cmdve);
}

static char	**ft_fill_cmdve2(t_tokens *tokens)
{
	char	**split;
	char	*buff;

	buff = ft_strdup(tokens->str);
	if (!buff)
		return (1);
	tokens = tokens->next;
	while (tokens->type == ARGS)
	{
		buff = ft_strjoin_s1c(buff, tokens->str, ' ');
		if (!buff)
			return (1);
		tokens = tokens->next;
	}
	split = ft_split(buff, ' ');
	free(buff);
	return (split);
}

static int	ft_fill_cmdve(char ***cmdve, t_cmds *cmd)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			cmdve[i] = ft_fill_cmdve2(tokens);
			if (!cmdve[i])
				return (1);
			i++;
		}
		else
			tokens = tokens->next;
	}
	return (0);
}

int	exec(t_data *data, t_cmds *cmd)
{
	char	***cmdve;

	cmdve = ft_make_cmdve(cmd);
	if (!cmdve)
		return (1);
	if (ft_fill_cmdve(cmdve, cmd))
		return (1);
	return (0);
}

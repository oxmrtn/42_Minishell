/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/05 15:28:02 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	***ft_make_cmdve(t_cmds *cmd)
{
	char		***cmdve;
	t_tokens	*tokens;
	int			n_cmds;

	tokens = cmd->tokens;
	n_cmds = 0;
	while (tokens)
	{
		if (tokens->type == CMD && n_cmds == 0)
			n_cmds++;
		if (tokens->type == PIPE && n_cmds > 0)
			n_cmds++;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (n_cmds + 1));
	if (!cmdve)
		return (NULL);
	cmdve[n_cmds] = NULL;
	return (cmdve);
}

static char	**ft_fill_cmdve2(t_tokens **tokens)
{
	char	**split;
	char	*buff;

	buff = ft_strdup((*tokens)->str);
	if (!buff)
		return (NULL);
	(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type == ARGS)
	{
		buff = ft_strjoin_c(buff, (*tokens)->str, ' ', 1);
		if (!buff)
			return (NULL);
		(*tokens) = (*tokens)->next;
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
	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			cmdve[i] = ft_fill_cmdve2(&tokens);
			if (!cmdve[i])
				return (1);
			i++;
		}
		else
			tokens = tokens->next;
	}
	return (0);
}

run_simple(t_data *data, t_cmds *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
	{
		if (is_outred(cmd))
			return (1);	
	}
	else
	{
		while (1)
		{
			endpid = waitpid(-1, &status, 0);
			if (endpid == pid)
				if (WIFEXITED(status))
					data->exit_status = WEXITSTATUS(status);
			if (endpid == -1)
				break ;
		}
	}
	return (0);
}

int	exec2(t_data *data, t_cmds *cmd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
	{
		if (is_inred(cmd, &i, data->cmdve))
			return (1);
		if (data->cmdve[1])
		{
			while (data->cmdve[i + 1])
				if (run_pipe(data, i, cmd, 0))
					return (1);
			if (run_pipe(data, i, cmd, 1))
				return (1);
		}
		else
			if (data, cmd)
				return (1);
	}
	else
		wait(NULL);
	return (0);
}

int	exec(t_data *data, t_cmds *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	data->cmdve = ft_make_cmdve(cmd);
	if (!data->cmdve)
		return (1);
	if (!data->cmdve[0])
		return (0);
	if (ft_fill_cmdve(data->cmdve, cmd))
		return (1);
	if (exec2(data, cmd, i))
		return (1);
	ft_free_cmdve(data->cmdve);
	return (0);
}

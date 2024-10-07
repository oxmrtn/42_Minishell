/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/07 19:04:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	reset_fds(t_data *data, int std)
{
	if (std == 0 || std == 2)
	{
		close(STDIN_FILENO);
		if (dup2(data->stdincpy, STDIN_FILENO) == -1)
			return (perror(NULL), 1);
		close(data->stdincpy);
		data->stdincpy = dup(STDIN_FILENO);
		if (data->stdincpy == -1)
			return (1);
	}
	if (std == 1 || std == 2)
	{
		close(STDOUT_FILENO);
		if (dup2(data->stdoutcpy, STDOUT_FILENO) == -1)
			return (perror(NULL), 1);
		close(data->stdoutcpy);
		data->stdoutcpy = dup(STDOUT_FILENO);
		if (data->stdoutcpy == -1)
			return (1);
	}
	return (0);
}

int	run_gtw(t_data *data, t_cmds *cmd, int *i, int islast)
{
	int	redirs;

	data->isoutred = 0;
	redirs = is_redirs(data, cmd, *i);
	if (redirs == 1)
		return (1);
	if (tmp_env_setup(data, cmd, *i))
		return (1);
	if (run_cmd(data, *i, islast))
		return (1);
	if (reset_fds(data, 1))
		return (1);
	if (data->envs->tmpenvve)
	{
		ft_free_env(&data->envs->tmpenv);
		data->envs->tmpenv = NULL;
		ft_free_split(data->envs->envve);
		data->envs->envve = data->envs->tmpenvve;
		data->envs->tmpenvve = NULL;
	}
	return (0);
}

static int	exec2(t_data *data, t_cmds *cmd)
{
	int	i;

	i = 0;
	while (i < data->cmdvesize - 1)
	{
		if (run_gtw(data, cmd, &i, 0))
			return (1);
		i++;
	}
	if (run_gtw(data, cmd, &i, 1))
		return (1);
	return (0);
}

int	exec(t_data *data, t_cmds *cmd)
{
	if (!cmd)
		return (0);
	data->cmdve = ft_make_cmdve(data, cmd);
	if (!data->cmdve)
		return (1);
	if (fill_cmdve(data->cmdve, cmd))
		return (1);
	if (cmds_path(data->cmdve, data))
		return (1);
	if (exec2(data, cmd))
		return (1);
	if (reset_fds(data, 0))
		return (1);
	if (data->heredoc)
	{
		ft_free_heredoc(data);
		data->heredoc = NULL;
	}
	ft_free_cmdve(data);
	data->cmdve = NULL;
	data->cmdvesize = 0;
	return (0);
}

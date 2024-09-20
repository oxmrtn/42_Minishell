/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/20 17:38:35 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	reset_fds(t_data *data, int std)
{
	if (std == 0 || std == 2)
	{
		if (dup2(data->stdincpy, STDIN_FILENO) == -1)
			return (perror(NULL), 1);
		data->stdincpy = dup(STDIN_FILENO);
		if (data->stdincpy == -1)
			return (1);
	}
	if (std == 1 || std == 2)
	{
		if (dup2(data->stdoutcpy, STDOUT_FILENO) == -1)
			return (perror(NULL), 1);
		data->stdoutcpy = dup(STDOUT_FILENO);
		if (data->stdoutcpy == -1)
			return (1);
	}
	return (0);
}

static int	exec2(t_data *data, t_cmds *cmd, int j)
{
	int	i;

	i = 0;
	while (i < (j - 1))
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
	int	j;

	if (!cmd)
		return (0);
	data->cmdve = ft_make_cmdve(cmd, &j);
	if (!data->cmdve)
		return (1);
	if (ft_fill_cmdve(data, data->cmdve, cmd))
		return (1);
	if (cmds_path(data->cmdve, data, j))
		return (1);
	if (exec2(data, cmd, j))
		return (1);
	if (data->envs->tmpenv)
	{
		tmp_env_clean(data);
		free(data->envs->envve);
		data->envs->envve = data->envs->tmpenv;
		data->envs->tmpenv = NULL;
	}
	ft_free_cmdve(data->cmdve);
	if (reset_fds(data, 0))
		return (1);
	return (0);
}

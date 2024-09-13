/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/13 14:17:46 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	reset_fds(t_data *data)
{
	if (dup2(data->stdincpy, STDIN_FILENO) == -1)
		return (perror(NULL), 1);
	if (dup2(data->stdoutcpy, STDOUT_FILENO) == -1)
		return (perror(NULL), 1);
	data->stdincpy = dup(STDIN_FILENO);
	data->stdoutcpy = dup(STDOUT_FILENO);
	if (data->stdincpy == -1 || data->stdoutcpy == -1)
		return (1);
	return (0);
}

static int	exec2(t_data *data, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (is_inred(cmd, &i))
		return (1);
	while (data->cmdve[i] && data->cmdve[i + 1])
		if (run_cmd(data, i++, 0))
			return (1);
	if (is_outred(cmd))
		return (1);
	if (data->cmdve[i])
		if (run_cmd(data, i, 1))
			return (1);
	if (reset_fds(data))
		return (1);
	return (0);
}

int	exec(t_data *data, t_cmds *cmd)
{
	if (!cmd)
		return (0);
	data->cmdve = ft_make_cmdve(cmd);
	if (!data->cmdve)
		return (1);
	if (ft_fill_cmdve(data->cmdve, cmd))
		return (1);
	if (cmds_path(data->cmdve, data))
		return (1);
	if (exec2(data, cmd))
		return (1);
	ft_free_cmdve(data->cmdve);
	return (0);
}

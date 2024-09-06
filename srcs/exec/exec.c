/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/06 18:27:33 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	exec_exit(t_data *data, int status)
{
	free_main(data);
	exit(status);
}

static void	exec3(t_data *data, t_cmds *cmd)
{
	int	i;

	i = 0;
	if (is_inred(cmd, &i, data->cmdve))
		exec_exit(data, 1);
	while (data->cmdve[i] && data->cmdve[i + 1])
		if (run_cmd(data, i++, cmd, 0))
			exec_exit(data, 1);
	if (data->cmdve[i])
		if (run_cmd(data, i, cmd, 1))
			exec_exit(data, 1);
	exec_exit(data, 0);
}

static int	exec2(t_data *data, t_cmds *cmd)
{
	pid_t	pid;
	pid_t	tmp_pid;
	int		child_status;
	int		retval;

	retval = 0;
	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
		exec3(data, cmd);
	else
	{
		while (1)
		{
			tmp_pid = waitpid(-1, &child_status, 0);
			if (tmp_pid == pid)
				if (WIFEXITED(child_status))
					retval = WEXITSTATUS(child_status);
			if (tmp_pid == -1)
				break ;
		}
	}
	return (retval);
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

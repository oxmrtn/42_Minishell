/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:49:23 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/02 18:01:36 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	run_child(char **cmdve, int *fds, t_cmds *cmd, int islast)
{
	close(fds[0]);
	if (islast)
		if (is_outred(cmd))
			return (1);
	if (islast == 0)
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (close(fds[1]), perror(NULL), 1);
	close(fds[1]);
	if (execve(cmdve[0], cmdve, NULL) == -1)
	{
		perror("exec: command not found");
		exit(127);
	}
	return (0);
}

static int	run_parent(pid_t pid, int *fds, t_data *data, int islast)
{
	pid_t	endpid;
	int		status;

	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (close(fds[0]), perror(NULL), 1);
	close(fds[0]);
	if (islast)
	{
		while (1 == 1)
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

int	run_cmd(char **cmdve, t_data *data, t_cmds *cmd, int islast)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (perror(NULL), 1);
	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
		if (run_child(cmdve, fds, cmd, islast))
			return (1);
	if (pid != 0)
		if (run_parent(pid, fds, data, islast))
			return (1);
	return (0);
}

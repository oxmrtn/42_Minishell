/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:49:23 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/01 14:29:11 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	cmd_isdir(t_data *data, char *cmd, int *fds)
{
	struct stat	cmdvestats;

	if (!ft_ultimate_compare(cmd, "~")
		|| (!stat(cmd, &cmdvestats) && S_ISDIR(cmdvestats.st_mode)))
	{
		close(fds[1]);
		ft_desc_error(cmd, "is a directory\n", 0);
		free_main(data);
		exit(126);
	}
}

static int	run_child(t_data *data, int i, int *fds, int islast)
{
	close(fds[0]);
	if (!islast)
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (close(fds[1]), perror(NULL), 1);
	close(fds[1]);
	if (!data->cmdve[i] || is_builtin(data->cmdve[i][0]))
	{
		free_main(data);
		exit(0);
	}
	if (is_outred(ft_get_last_commands(data->cmds), i))
		return (1);
	cmd_isdir(data, data->cmdve[i][0], fds);
	if (execve(data->cmdve[i][0], data->cmdve[i], data->envs->envve) == -1)
	{
		ft_desc_error("command not found", data->cmdve[i][0], 1);
		perror(NULL);
		free_main(data);
		exit(127);
	}
	return (0);
}

static int	run_parent(t_data *data, int i, int *fds, int islast)
{
	int	builtin_check;

	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (close(fds[0]), perror(NULL), 1);
	close(fds[0]);
	if (!data->cmdve[i])
	{
		close(fds[1]);
		if (is_outred(ft_get_last_commands(data->cmds), i))
			return (1);
		return (0);
	}
	builtin_check = is_builtin(data->cmdve[i][0]);
	if (!islast && builtin_check)
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (close(fds[1]), perror(NULL), 1);
	close(fds[1]);
	if (builtin_check)
	{
		if (is_outred(ft_get_last_commands(data->cmds), i))
			return (1);
		if (exec_builtin(data, data->cmdve[i]) == -100)
			return (1);
	}
	return (0);
}

static void	wait_exec(t_data *data, int i, pid_t pid)
{
	pid_t	endpid;
	int		status;

	while (1)
	{
		endpid = waitpid(-1, &status, 0);
		if (endpid == pid)
			if (WIFEXITED(status) && data->cmdve[i]
				&& !is_builtin(data->cmdve[i][0]))
				data->exit_status = WEXITSTATUS(status);
		if (endpid == -1)
			break ;
	}
}

int	run_cmd(t_data *data, int i, int islast)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (perror(NULL), 1);
	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
		if (run_child(data, i, fds, islast))
			return (1);
	if (pid != 0)
	{
		if (run_parent(data, i, fds, islast))
			return (1);
		if (islast)
			wait_exec(data, i, pid);
	}
	return (0);
}

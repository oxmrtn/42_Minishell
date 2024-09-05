/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:32:56 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/02 18:12:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	heredoc_gnl(char *limiter, int *fds)
{
	char	*buff;
	int		cmp_len;

	buff = get_next_line(0);
	while (buff)
	{
		cmp_len = ft_max((ft_strlen(buff) - 1), ft_strlen(limiter));
		if (ft_strncmp(buff, limiter, cmp_len) == 0)
		{
			free(buff);
			close(fds[1]);
			exit(0);
		}
		ft_putstr_fd(buff, fds[1]);
		free(buff);
		buff = get_next_line(0);
	}
}

int	run_heredoc(char *limiter)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (perror(NULL), 1);
	pid = fork();
	if (pid == -1)
		return (perror(NULL), 1);
	if (pid == 0)
	{
		close(fds[0]);
		heredoc_gnl(limiter, fds);
		close(fds[1]);
		exit(0);
	}
	if (pid != 0)
	{
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (perror(NULL), 1);
		close(fds[0]);
		wait(NULL);
	}
	return (0);
}

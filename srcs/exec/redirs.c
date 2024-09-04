/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/02 18:15:09 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	dup_pipe_no_inred(void)
{
	int	fds[2];

	if (pipe(fds) == -1)
		return (perror(NULL), 1);
	close(fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (close(fds[0]), perror(NULL), 1);
	close(fds[0]);
	return (0);
}

static int	dup_inred(char *infile, int *i, char ***cmdve)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("infile");
		*i += 1;
		if (cmdve[1])
			if (dup_pipe_no_inred())
				return (1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close (fd), perror(NULL), 1);
		close (fd);
	}
	return (0);
}

int	is_inred(t_cmds *cmd, int *i, char ***cmdve)
{
	t_tokens	*tokens;

	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == INFILE)
			if (dup_inred(tokens->str, i, cmdve))
				return (1);
		if (tokens->type == LIMITER)
			if (run_heredoc(tokens->str))
				return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	is_outred(t_cmds *cmd)
{
	t_tokens	*tokens;
	int			fd;

	fd = 1;
	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == APPEND)
			fd = open(tokens->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (tokens->type == OUTFILE)
			fd = open(tokens->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (tokens->type == APPEND || tokens->type == OUTFILE)
			break ;
		tokens = tokens->next;
	}
	if (fd == -1)
		return (perror("outfile"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror(NULL), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/19 14:46:59 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	dup_inred(char *infile, int *i)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("infile");
		*i += 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close (fd), perror(NULL), 1);
		close (fd);
	}
	return (0);
}

static int	dup_heredoc(void)
{
	int	fd;

	fd = open(".heredoc", O_CREAT, O_TRUNC, O_RDONLY);
	if (fd == -1)
		return (perror("heredoc"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close (fd), perror(NULL), 1);
	close (fd);
	return (0);
}

static t_tokens	*is_inred2(t_cmds *cmd, int i)
{
	t_tokens	*tokens;
	int			j;

	tokens = cmd->tokens;
	j = 0;
	while (tokens && j < i)
	{
		if ((tokens->type == INFILE || tokens->type == LIMITER)
			&& tokens->next && tokens->next->type == CMD)
			j++;
		tokens = tokens->next;
	}
	return (tokens);
}

int	is_inred(t_cmds *cmd, int *i)
{
	t_tokens	*tokens;
	int			retval;

	retval = 3;
	tokens = is_inred2(cmd, *i);
	while (tokens)
	{
		if (tokens->type == INFILE && tokens->next && tokens->next->type == CMD)
			if (dup_inred(tokens->str, i))
				return (-1);
		if (tokens->type == LIMITER && tokens->next
			&& tokens->next->type == CMD)
			if (dup_heredoc())
				return (-1);
		if ((tokens->type == INFILE || tokens->type == LIMITER)
			&& tokens->next && tokens->next->type == CMD)
		{
			retval = 0;
			break ;
		}
		tokens = tokens->next;
	}
	return (retval);
}

int	is_outred(t_cmds *cmd)
{
	t_tokens	*tokens;
	int			fd;

	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == APPEND)
			fd = open(tokens->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (tokens->type == OUTFILE)
			fd = open(tokens->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (tokens->type == APPEND || tokens->type == OUTFILE)
		{
			if (fd == -1)
				return (perror("outfile"), 1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror(NULL), 1);
			break ;
		}
		tokens = tokens->next;
	}
	return (0);
}

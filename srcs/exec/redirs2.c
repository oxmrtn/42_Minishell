/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/23 19:05:11 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_tokens	*skip_tokens(t_cmds *cmd, int i, int toskip)
{
	t_tokens	*tokens;
	int			j;

	tokens = cmd->tokens;
	j = 0;
	while (tokens && j < i)
	{
		if ((tokens->type == OUTFILE || tokens->type == APPEND)
			&& tokens->next && tokens->next->type == PIPE && toskip == 0)
			j++;
		if ((tokens->type == INFILE || tokens->type == LIMITER)
			&& tokens->next && tokens->next->type == PIPE && toskip == 1)
			j++;
		if ((tokens->type == ENV)
			&& tokens->next && tokens->next->type != ENV && toskip == 2)
			j++;
		tokens = tokens->next;
	}
	return (tokens);
}

static int	dup_outred(char *outfile, int is_append)
{
	int	fd;

	if (is_append)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("outfile"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror(NULL), 1);
	close(fd);
	return (0);
}

int	is_outred(t_cmds *cmd, int i)
{
	t_tokens	*tokens;

	tokens = skip_tokens(cmd, i, 0);
	while (tokens)
	{
		if (tokens->type == OUTFILE)
			if (dup_outred(tokens->str, 0))
				return (1);
		if (tokens->type == APPEND)
			if (dup_outred(tokens->str, 1))
				return (1);
		if ((tokens->type == OUTFILE || tokens->type == APPEND)
			&& (!tokens->next || (tokens->next && tokens->next->type == PIPE)))
			break ;
		tokens = tokens->next;
	}
	return (0);
}

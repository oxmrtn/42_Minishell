/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/03 19:01:11 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_tokens	*skip_tokens(t_cmds *cmd, int i)
{
	t_tokens	*tokens;
	int			j;

	tokens = cmd->tokens;
	j = 0;
	while (tokens && j < i)
	{
		if (tokens->type == PIPE)
			j++;
		tokens = tokens->next;
	}
	return (tokens);
}

static int	dup_inred(t_data *data, char *infile, int i)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_desc_error("infile", infile, 1, NULL);
		ft_free_split(data->cmdve[i]);
		data->cmdve[i] = NULL;
		return (2);
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

	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		ft_desc_error("heredoc", ".heredoc", 1, NULL);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close (fd), perror(NULL), 1);
	close (fd);
	if (unlink(".heredoc") == -1)
		return (1);
	return (0);
}

static int	dup_outred(t_data *data, char *outfile, int is_append, int i)
{
	int	fd;

	if (is_append)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_desc_error("outfile", outfile, 1, NULL);
		ft_free_split(data->cmdve[i]);
		data->cmdve[i] = NULL;
		return (2);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror(NULL), 1);
	close(fd);
	data->isoutred = 1;
	return (0);
}

int	is_redirs(t_data *data, t_cmds *cmd, int i)
{
	int			retval;
	t_tokens	*tokens;

	retval = 0;
	tokens = skip_tokens(cmd, i);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == APPEND)
			if (dup_outred(data, tokens->str, 1, i))
				return (1);
		if (tokens->type == LIMITER)
			if (dup_heredoc())
				return (1);
		if (tokens->type == OUTFILE)
			retval = dup_outred(data, tokens->str, 0, i);
		if (tokens->type == INFILE)
			retval = dup_inred(data, tokens->str, i);
		if (retval == 1 || retval == 2)
			return (retval);
		tokens = tokens->next;
	}
	return (0);
}

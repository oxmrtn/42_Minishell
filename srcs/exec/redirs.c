/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/02 19:00:44 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	dup_inred(char *infile, int *i)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_desc_error("infile", infile, 1);
		perror(NULL);
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
	if (unlink(".heredoc") == -1)
		return (1);
	return (0);
}

static size_t	is_inred2(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == INFILE || tokens->type == LIMITER)
			i++;
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (i);
}

int	is_inred(t_cmds *cmd, int *i)
{
	t_tokens	*tokens;
	size_t		j;
	size_t		k;

	tokens = skip_tokens(cmd, *i);
	j = is_inred2(tokens);
	k = 0;
	while (tokens)
	{
		if ((tokens->type == INFILE || tokens->type == LIMITER) && j != k)
			k++;
		if (tokens->type == INFILE && j == k)
			if (dup_inred(tokens->str, i))
				return (1);
		if (tokens->type == LIMITER && j == k)
			if (dup_heredoc())
				return (1);
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (0);
}

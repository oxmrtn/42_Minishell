/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:37:08 by ebengtss          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/23 15:02:52 by ebengtss         ###   ########.fr       */
=======
/*   Updated: 2024/09/18 17:18:17 by mtrullar         ###   ########.fr       */
>>>>>>> Parsing
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

int	is_inred(t_cmds *cmd, int *i)
{
	t_tokens	*tokens;

	tokens = skip_tokens(cmd, *i, 1);
	while (tokens)
	{
		if (tokens->type == INFILE && tokens->next
			&& tokens->next->type != REDIR)
			if (dup_inred(tokens->str, i))
				return (1);
		if (tokens->type == LIMITER && tokens->next
			&& tokens->next->type != REDIR)
			if (dup_heredoc())
				return (1);
		if ((tokens->type == INFILE || tokens->type == LIMITER)
			&& (!tokens->next || (tokens->next && tokens->next->type != REDIR)))
			break ;
		tokens = tokens->next;
	}
	return (0);
}

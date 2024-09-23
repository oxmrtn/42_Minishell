/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/23 18:50:29 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	***ft_make_cmdve(t_cmds *cmd, int *j)
{
	char		***cmdve;
	t_tokens	*tokens;

	tokens = cmd->tokens;
	*j = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			*j += 1;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (*j + 1));
	if (!cmdve)
		return (NULL);
	cmdve[*j] = NULL;
	return (cmdve);
}

static int	ft_is_cmdve(t_tokens *tokens)
{
	if (tokens->type == OUTFILE || tokens->type == INFILE
		|| tokens->type == REDIR)
		return (2);
	if (tokens->type == CMD || tokens->type == ARGS)
		return (1);
	return (0);
}

static char**	ft_fill_cmdve3(t_tokens *tokens)
{
	char	**cmdve;
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (ft_is_cmdve(tokens) == 1)
			i++;
		if (tokens->next && !ft_is_cmdve(tokens->next))
			break ;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (i + 1));
	if (!cmdve)
		return (NULL);
	cmdve[i] = NULL;
	return (cmdve);
}

static char	**ft_fill_cmdve2(t_tokens **tokens)
{
	char		**cmdve;
	size_t		i;

	i = 0;
	cmdve = ft_fill_cmdve3(*tokens);
	if (!cmdve)
		return (NULL);
	while ((*tokens))
	{
		if (ft_is_cmdve(*tokens) == 1)
		{
			cmdve[i] = ft_strdup((*tokens)->str);
			if (!cmdve[i])
				return (ft_free_split(cmdve), NULL);
			i++;
		}
		if ((*tokens)->next && !ft_is_cmdve((*tokens)->next))
			break ;
		*tokens = (*tokens)->next;
	}
	return (cmdve);
}

int	ft_fill_cmdve(char ***cmdve, t_cmds *cmd)
{
	t_tokens	*tokens;
	int			i;
	int			check;

	i = 0;
	check = 0;
	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			cmdve[i] = ft_fill_cmdve2(&tokens);
			if (!cmdve[i++])
				return (1);
			check = 1;
		}
		if (tokens && tokens->type == PIPE && !check)
			cmdve[i++] = NULL;
		if (tokens)
			tokens = tokens->next;
		check = 0;
	}
	if (!i)
		cmdve[i] = NULL;
	return (0);
}

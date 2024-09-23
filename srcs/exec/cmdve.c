/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/23 14:46:49 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	***ft_make_cmdve(t_cmds *cmd, int *j)
{
	char		***cmdve;
	t_tokens	*tokens;

	tokens = cmd->tokens;
	*j = 0;
	while (tokens)
	{
		if ((tokens->type == CMD || tokens->type == PIPE) && *j == 0)
			*j += 1;
		if (tokens->type == PIPE && *j > 0)
			*j += 1;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (*j + 1));
	if (!cmdve)
		return (NULL);
	cmdve[*j] = NULL;
	return (cmdve);
}

static void	ft_fill_cmdve3(char ***cmdve, t_tokens **tokens, int *i, int *check)
{
	if (!(*check))
	{
		cmdve[*i] = NULL;
		*i += 1;
	}
	*tokens = (*tokens)->next;
	*check = 0;
}

static char	**ft_fill_cmdve2(t_tokens **tokens)
{
	char		**cmdve;
	t_tokens	*tokencpy;
	size_t		i;

	tokencpy = *tokens;
	i = 0;
	while (tokencpy && (tokencpy->type == CMD || tokencpy->type == ARGS))
	{
		tokencpy = tokencpy->next;
		i++;
	}
	cmdve = malloc(sizeof(char *) * (i + 1));
	if (!cmdve)
		return (NULL);
	cmdve[i] = NULL;
	i = 0;
	while ((*tokens) && ((*tokens)->type == CMD || (*tokens)->type == ARGS))
	{
		cmdve[i] = ft_strdup((*tokens)->str);
		if (!cmdve[i])
			return (ft_free_split(cmdve), NULL);
		(*tokens) = (*tokens)->next;
		i++;
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
		if (tokens && tokens->type == PIPE)
			ft_fill_cmdve3(cmdve, &tokens, &i, &check);
		else if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

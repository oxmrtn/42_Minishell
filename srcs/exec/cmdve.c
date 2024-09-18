/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/13 16:06:38 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	***ft_make_cmdve(t_cmds *cmd)
{
	char		***cmdve;
	t_tokens	*tokens;
	int			n_cmds;

	tokens = cmd->tokens;
	n_cmds = 0;
	while (tokens)
	{
		if (tokens->type == CMD && n_cmds == 0)
			n_cmds++;
		if (tokens->type == PIPE && n_cmds > 0)
			n_cmds++;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (n_cmds + 1));
	if (!cmdve)
		return (NULL);
	cmdve[n_cmds] = NULL;
	return (cmdve);
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

	i = 0;
	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			cmdve[i] = ft_fill_cmdve2(&tokens);
			if (!cmdve[i])
				return (1);
			i++;
		}
		else
			tokens = tokens->next;
	}
	return (0);
}
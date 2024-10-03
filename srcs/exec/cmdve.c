/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/03 15:54:16 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	***ft_make_cmdve(t_data *data, t_cmds *cmd)
{
	char		***cmdve;
	t_tokens	*tokens;

	tokens = cmd->tokens;
	data->cmdvesize = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			data->cmdvesize++;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (data->cmdvesize + 1));
	if (!cmdve)
		return (NULL);
	cmdve[data->cmdvesize] = NULL;
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

static char	**ft_fill_cmdve3(t_tokens *tokens)
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

static int	ft_fill_cmdve2(char ***cmdve, int j, int *check, t_tokens **tokens)
{
	size_t		i;

	i = 0;
	cmdve[j] = ft_fill_cmdve3(*tokens);
	if (!cmdve[j])
		return (1);
	while ((*tokens))
	{
		if (ft_is_cmdve(*tokens) == 1)
		{
			cmdve[j][i] = ft_strdup((*tokens)->str);
			if (!cmdve[j][i])
				return (1);
			i++;
		}
		if ((*tokens)->next && !ft_is_cmdve((*tokens)->next))
			break ;
		*tokens = (*tokens)->next;
	}
	*check = 1;
	return (0);
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
			if (ft_fill_cmdve2(cmdve, i++, &check, &tokens))
				return (1);
		if (tokens && tokens->type == PIPE)
		{
			if (!check)
				cmdve[i++] = NULL;
			check = 0;
		}
		if (tokens)
			tokens = tokens->next;
	}
	if (!i)
		cmdve[i] = NULL;
	return (0);
}

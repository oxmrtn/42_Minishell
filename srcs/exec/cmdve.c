/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/07 16:02:37 by ebengtss         ###   ########.fr       */
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
		return (data->cmdvesize = 0, NULL);
	cmdve[data->cmdvesize] = NULL;
	return (cmdve);
}

static char	**fill_cmdve4(t_tokens *tokens)
{
	char	**cmdve;
	size_t	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == CMD || tokens->type == ARGS)
			i++;
		tokens = tokens->next;
	}
	cmdve = malloc(sizeof(char *) * (i + 1));
	if (!cmdve)
		return (NULL);
	cmdve[i] = NULL;
	return (cmdve);
}

static int	fill_cmdve3(char ***cmdve, int j, int *check, t_tokens **tokens)
{
	size_t		i;

	i = 0;
	cmdve[j] = fill_cmdve4(*tokens);
	if (!cmdve[j])
		return (1);
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == CMD || (*tokens)->type == ARGS)
		{
			cmdve[j][i] = ft_strdup((*tokens)->str);
			if (!cmdve[j][i])
				return (1);
			i++;
		}
		*tokens = (*tokens)->next;
	}
	*check = 1;
	return (0);
}

static int	fill_cmdve2(t_data *data, char ***cmdve, t_tokens *tokens, int *i)
{
	t_nk	check;

	check.j = 0;
	check.k = 0;
	while (tokens)
	{
		if (tokens->type == LIMITER)
			check.k = 1;
		if (tokens->type == CMD)
			if (fill_cmdve3(cmdve, (*i)++, &(check.j), &tokens))
				return (1);
		if (tokens && (tokens->type == PIPE || !tokens->next))
		{
			if (check.k && cmdve[*i - 1] && *i - 1 != data->iheredoc)
				ft_free_split(cmdve[--(*i)]);
			if (!check.j || check.k)
				cmdve[(*i)++] = NULL;
			check.j = 0;
			check.k = 0;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

int	fill_cmdve(t_data *data, char ***cmdve, t_cmds *cmd)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	tokens = cmd->tokens;
	if (fill_cmdve2(data, cmdve, tokens, &i))
		return (1);
	if (!i)
		cmdve[i] = NULL;
	return (0);
}

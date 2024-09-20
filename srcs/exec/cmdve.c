/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:53 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/20 18:40:43 by ebengtss         ###   ########.fr       */
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

static int	ft_env_setup(t_data *data, t_tokens **tokens)
{
	while ((*tokens) && ((*tokens)->type == ENV))
	{
		if (ft_ultimate_compare((*tokens)->str, "env") != 0)
			if (tmp_env_add(data, (*tokens)->str))
				return (tmp_env_clean(data), 1);
		(*tokens) = (*tokens)->next;
	}
	data->envs->tmpenv = data->envs->envve;
	data->envs->envve = env_to_tab(data);
	if (!data->envs->envve)
		return (1);
	return (0);
}

static void	ft_fill_cmdve3(char ***cmdve, t_tokens **tokens, int *i)
{
	*tokens = (*tokens)->next;
	cmdve[*i] = NULL;
	*i += 1;
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

int	ft_fill_cmdve(t_data *data, char ***cmdve, t_cmds *cmd)
{
	t_tokens	*tokens;
	int			i;
	int			j;

	i = 0;
	tokens = cmd->tokens;
	while (tokens)
	{
		j = i;
		if (tokens->type == ENV)
			if (ft_env_setup(data, &tokens))
				return (1);
		if (tokens->type == CMD)
		{
			cmdve[i] = ft_fill_cmdve2(&tokens);
			if (!cmdve[i++])
				return (1);
		}
		if (tokens && tokens->type == PIPE && i == j)
			ft_fill_cmdve3(cmdve, &tokens, &i);
		if (tokens && i == j)
			tokens = tokens->next;
	}
	return (0);
}

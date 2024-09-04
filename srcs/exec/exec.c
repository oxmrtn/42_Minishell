/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:57:50 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/04 16:54:36 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	***ft_make_cmdve(t_cmds *cmd)
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
	if (n_cmds == 0)
		return (NULL);
	cmdve = malloc(sizeof(char *) * (n_cmds + 1));
	if (!cmdve)
		return (NULL);
	cmdve[n_cmds] = NULL;
	return (cmdve);
}

static char	**ft_fill_cmdve2(t_tokens **tokens)
{
	char	**split;
	char	*buff;

	buff = ft_strdup((*tokens)->str);
	if (!buff)
		return (NULL);
	(*tokens) = (*tokens)->next;
	while ((*tokens) && (*tokens)->type == ARGS)
	{
		buff = ft_strjoin_c(buff, (*tokens)->str, ' ', 1);
		if (!buff)
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	split = ft_split(buff, ' ');
	free(buff);
	return (split);
}

static int	ft_fill_cmdve(char ***cmdve, t_cmds *cmd)
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

int	exec(t_data *data, t_cmds *cmd)
{
	char	***cmdve;
	int		i;

	i = 0;
	cmdve = ft_make_cmdve(cmd);
	if (!cmdve)
		return (1);
	if (ft_fill_cmdve(cmdve, cmd))
		return (cleanup_exec(cmdve), 1);
	if (is_inred(cmd, &i, cmdve))
		return (cleanup_exec(cmdve), 1);
	while (cmdve[i + 1])
		if (run_cmd(cmdve[i], data, cmd, 0))
			return (cleanup_exec(cmdve), 1);
	if (run_cmd(cmdve[i], data, cmd, 1))
		return (cleanup_exec(cmdve), 1);
	cleanup_exec(cmdve);
	return (0);
}

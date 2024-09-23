/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:27:05 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/23 14:44:02 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	if (env_update(data->envs->env, cmdve))
		return (0);
	node = envnew_gtw(cmdve, 0);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->l_env, node);
	return (0);
}

void	tmp_env_clean(t_data *data)
{
	t_env	*l_node;

	l_node = data->envs->l_env;
	if (l_node->next)
	{
		ft_free_env(&l_node->next);
		data->envs->l_env->next = NULL;
	}
}

int tmp_env_setup(t_data *data, t_cmds *cmd, int i)
{
	t_tokens	*tokens;

	tokens = skip_tokens(cmd, i, 2);
	while (tokens)
	{
		if (tokens->type == ENV
            && ft_ultimate_compare(tokens->str, "env") != 0)
			if (tmp_env_add(data, tokens->str))
				return (1);
		if (tokens->type == ENV
			&& (!tokens->next || (tokens->next && tokens->next->type != ENV)))
			break ;
		tokens = tokens->next;
	}
	data->envs->tmpenv = data->envs->envve;
	data->envs->envve = env_to_tab(data);
	if (!data->envs->envve)
		return (1);
	return (0);
}

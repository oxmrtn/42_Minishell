/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionnal_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:38:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/23 16:09:15 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_invalid_syntax(t_cmds *to_free)
{
	free(to_free->cmd);
	ft_free_tokens(to_free->tokens);
	free(to_free);
}

static void	ft_free_var(t_var *node)
{
	t_var	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->name);
		free(temp->content);
		free(temp);
	}
}

void	ft_omega_free(t_data *data)
{
	if (data->cmds)
	{
		ft_write_history(data->cmds);
		ft_free_commands(data->cmds);
	}
	if (data->envs)
		ft_free_env(&data->envs->env);
	if (data->var)
		ft_free_var(data->var);
	if (data->cmdve)
		ft_free_cmdve(data->cmdve);
	free(data);
}

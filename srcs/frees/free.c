/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:35:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 16:32:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_tokens(t_tokens *tok)
{
	t_tokens	*tmp;

	while (tok)
	{
		tmp = tok;		
		tok = tok->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_commands(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		ft_free_tokens(tmp->tokens);
		free(tmp->cmd);
		free(tmp);
	}
}

void	ft_free_cmdve(char ***cmdve)
{
	int i;

	i = 0;
	if (*cmdve)
	{
		if (**cmdve)
		{
			while (cmdve[i])
			{
				ft_free_split(cmdve[i]);
				i++;
			}
		}
		free(cmdve);
		cmdve = NULL;
	}
}

void	ft_free_env(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		free(tmp);
	}
}

void	free_main(t_data *data)
{
	if (data)
	{
		if (data->cmds)
			ft_free_commands(data->cmds);
		if (data->envs)
		{
			if (data->envs->env)
				ft_free_env(&data->envs->env);
			if (data->envs->exp)
				ft_free_env(&data->envs->exp);
			if (data->envs->tmpenv)
				ft_free_split(data->envs->tmpenv);
			if (data->envs->envve)
				ft_free_split(data->envs->envve);
			free(data->envs);
		}
		if (data->cmdve)
			ft_free_cmdve(data->cmdve);
		free(data);
	}
}


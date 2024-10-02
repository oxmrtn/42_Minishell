/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:35:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 19:08:54 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_cmdve(char ***cmdve)
{
	int	i;

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

void	ft_free_envs(t_data *data)
{
	if (data->envs->env)
		ft_free_env(&data->envs->env);
	if (data->envs->exp)
		ft_free_env(&data->envs->exp);
	if (data->envs->tmpenv)
		ft_free_env(&data->envs->tmpenv);
	if (data->envs->tmpenvve)
		ft_free_split(data->envs->tmpenvve);
	if (data->envs->envve)
		ft_free_split(data->envs->envve);
	free(data->envs);
}

void	free_main(t_data *data)
{
	if (data)
	{
		if (data->cmds)
		{
			ft_write_history(data->cmds);
			ft_free_commands(data->cmds);
		}
		if (data->read)
			free(data->read);
		if (data->envs)
			ft_free_envs(data);
		if (data->var)
			ft_free_var(data->var);
		if (data->cmdve)
			ft_free_cmdve(data->cmdve);
		free(data);
		clear_history();
	}
}

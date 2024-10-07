/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:35:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/07 17:31:46 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_heredoc(t_data *data)
{
	t_hd	*head;
	t_hd	*tmp;

	head = data->heredoc;
	while (head)
	{
		close(head->fd);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	data->heredoc = NULL;
}

void	ft_free_cmdve(t_data *data)
{
	int		i;
	char	***cmdve;

	i = 0;
	cmdve = data->cmdve;
	while (i < data->cmdvesize)
	{
		if (cmdve[i])
			ft_free_split(cmdve[i]);
		i++;
	}
	if (data->cmdvesize > 0)
		free(cmdve);
	cmdve = NULL;
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

void	free_main(t_data *data, int i)
{
	if (data)
	{
		if (data->cmds)
		{
			if (i == 1)
				ft_write_history(data->cmds);
			ft_free_commands(data->cmds);
		}
		if (data->read)
			free(data->read);
		if (data->envs)
			ft_free_envs(data);
		if (data->var)
			ft_free_var(data->var);
		ft_free_cmdve(data);
		free(data);
		clear_history();
	}
}

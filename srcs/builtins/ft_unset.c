/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:13 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/26 16:18:46 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	env_del(t_data *data, t_env *lst, char *delkey)
{
	int	check;

	check = 0;
	while (lst)
	{
		if (!ft_ultimate_compare(lst->key, delkey))
		{
			ft_envdelone(data, lst);
			check = 1;
		}
		lst = lst->next;
	}
	return (check);
}

int	ft_unset(t_data *data, char **cmdve)
{
	size_t	i;
	int		check;

	i = 1;
	check = 0;
	while (cmdve[i])
	{
		if (ft_ultimate_compare(cmdve[i], "_") != 0)
		{
			check += env_del(data, data->envs->env, cmdve[i]);
			env_del(data, data->envs->exp, cmdve[i]);
		}
		i++;
	}
	if (check > 0)
	{
		if (data->envs->envve)
			free(data->envs->envve);
		data->envs->envve = env_to_tab(data);
		if (!data->envs->envve)
			return (1);
	}
	return (0);
}

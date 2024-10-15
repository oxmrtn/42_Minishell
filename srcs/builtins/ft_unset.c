/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:13 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/11 17:50:40 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	env_del(t_data *data, t_env *lst, char *delkey)
{
	int		check;
	t_env	*tmp;

	check = 0;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (!ft_ultimate_compare(tmp->key, delkey))
		{
			ft_envdelone(data, tmp);
			check = 1;
		}
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
		if (envtab_update(data))
			return (-100);
	return (0);
}

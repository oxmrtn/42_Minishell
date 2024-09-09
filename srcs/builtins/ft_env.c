/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/09 17:00:54 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	node = ft_envnew(cmdve);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->l_env, node);
	return (0);
}

static void	env_clean(t_data *data)
{
	t_env	*l_node;

	l_node = data->envs->l_env;
	while (l_node->next)
		ft_envdelone(data, l_node->next, 1);
}

int	ft_env(t_data *data, char **cmdve)
{
	size_t	i;

	if (!cmdve[1])
		print_env(data->envs->env);
	else
	{
		i = 1;
		while (cmdve[i])
		{
			if (strchr(cmdve[i], '='))
			{
				if (tmp_env_add(data, cmdve[i]))
					return (env_clean(data), 1);
			}
			else
				//exec
			i++;
		}
		print_env(data->envs->env);
		env_clean(data);
	}
	return (0);
}

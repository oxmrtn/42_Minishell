/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:08:59 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/27 18:59:28 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_envadd_front(t_env **lst, t_env *new)
{
	new->prev = NULL;
	if (*lst)
	{
		if ((*lst)->prev)
		{
			(*lst)->prev->next = new;
			new->prev = (*lst)->prev;
		}
		(*lst)->prev = new;
		new->next = *lst;
	}
	else
		*lst = new;
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*elem;

	if (!(*lst))
		ft_envadd_front(lst, new);
	else
	{
		elem = ft_envlast(*lst);
		elem->next = new;
		new->prev = elem;
		new->next = NULL;
	}
}

static t_env	*ft_envdup2(t_env *env)
{
	char	*keydup;
	char	*valdup;

	keydup = ft_strdup(env->key);
	if (!keydup)
		return (NULL);
	valdup = ft_strdup(env->val);
	if (!valdup)
		return (free(keydup), NULL);
	return (ft_envnew(keydup, valdup, 0));
}

int	ft_envdup(t_data *data)
{
	t_env	*env;
	t_env	*envdup;

	env = data->envs->env;
	while (env)
	{
		envdup = ft_envdup2(env);
		if (!envdup)
			return (1);
		ft_envadd_back(&data->envs->tmpenv, envdup);
		env = env->next;
	}
	return (0);
}

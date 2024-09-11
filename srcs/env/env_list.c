/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:55:26 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/11 15:38:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*ft_envnew(char *key, char *val, int is_exp_no_val)
{
	t_env	*newelem;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
		return (NULL);
	newelem->key = key;
	newelem->val = val;
	newelem->exp_noval = is_exp_no_val;
	newelem->prev = NULL;
	newelem->next = NULL;
	return (newelem);
}

size_t	ft_envsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envdelone(t_data *data, t_env *node, int which)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else if (which)
		data->envs->env = node->next;
	else
		data->envs->exp = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node == data->envs->l_env && node->prev)
		data->envs->l_env = node->prev;
	else if (node == data->envs->l_env && node->next)
		data->envs->l_env = node->next;
	else
		data->envs->l_env = NULL;
	free(node->key);
	free(node->val);
	free(node);
}

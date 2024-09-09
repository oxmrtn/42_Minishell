/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:55:26 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/09 16:46:47 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*ft_envnew(char *str)
{
	t_env	*newelem;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
		return (NULL);
	newelem->content = ft_strdup(str);
	if (!newelem->content)
		return (free(newelem), NULL);
	newelem->prev = NULL;
	newelem->next = NULL;
	return (newelem);
}

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
	if (node == data->envs->l_exp && node->prev)
		data->envs->l_exp = node->prev;
	else if (node == data->envs->l_exp && node->next)
		data->envs->l_exp = node->next;
	else
		data->envs->l_exp = NULL;
	free(node->content);
	free(node);
}

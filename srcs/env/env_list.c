/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:55:26 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/06 16:03:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*ft_envnew(char *str)
{
	t_env	*newelem;

	newelem = malloc(sizeof(t_env));
	if (!newelem)
		return (NULL);
	newelem->content = str;
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

void	ft_envdelone(t_env *lst, t_env *todel)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst == todel)
		{
			lst->prev->next = lst->next;
			lst->next->prev = lst->prev;
			free(lst);
			break ;
		}
		lst = lst->next;
	}
}

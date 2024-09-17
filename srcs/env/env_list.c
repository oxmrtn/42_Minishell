/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:55:26 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/17 16:17:45 by ebengtss         ###   ########.fr       */
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

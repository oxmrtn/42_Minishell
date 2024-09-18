/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:08:59 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/18 12:09:14 by ebengtss         ###   ########.fr       */
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
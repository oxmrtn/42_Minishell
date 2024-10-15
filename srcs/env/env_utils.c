/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:32:48 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/15 16:56:06 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	env_update_keyval(t_env *lst, char *key, char *newval)
{
	while (lst)
	{
		if (!ft_ultimate_compare(key, lst->key))
		{
			if (lst->val)
				free(lst->val);
			if (newval)
				lst->val = ft_strdup(newval);
			else
				lst->val = NULL;
			if (!lst->val && newval)
				return (1);
			break ;
		}
		lst = lst->next;
	}
	return (0);
}

char	*env_getval_key(t_env *lst, char *key)
{
	char	*lookupval;

	lookupval = NULL;
	while (lst)
	{
		if (!ft_ultimate_compare(key, lst->key))
		{
			if (lst->val)
				lookupval = ft_strdup(lst->val);
			break ;
		}
		lst = lst->next;
	}
	return (lookupval);
}

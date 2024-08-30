/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:51:54 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 18:11:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!(*lst))
		ft_envadd_front(lst, new);
	else
	{
		last = ft_envlast(*lst);
		last->next = new;
	}
}

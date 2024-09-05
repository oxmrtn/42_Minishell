/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:38:58 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 17:41:27 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_envsize(t_env *lst)
{
	int		i;
	t_env	*current;

	if (!lst)
		return (0);
	i = 1;
	current = lst;
	while (current->next)
	{
		i++;
		current = current->next;
	}
	return (i);
}

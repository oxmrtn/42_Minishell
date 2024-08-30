/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:24 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 17:41:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_envclear(t_env **lst, void (*del)(void *))
{
	t_env	*tempo;

	while (*lst)
	{
		tempo = (*lst)->next;
		ft_lstdelone(*(lst), del);
		*lst = tempo;
	}
}

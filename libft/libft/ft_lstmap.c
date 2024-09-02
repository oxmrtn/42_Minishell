/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:58:31 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 18:12:49 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

t_env	*ft_envmap(t_env *lst, void *(*f)(void *), void (*del)(void *))
{
	t_env	*result;
	t_env	*tempo;

	result = NULL;
	while (lst)
	{
		tempo = ft_envnew(f(lst->content));
		if (!tempo)
		{
			ft_envclear(&result, del);
			return (NULL);
		}
		ft_envadd_back(&result, tempo);
		lst = lst->next;
	}
	return (result);
}

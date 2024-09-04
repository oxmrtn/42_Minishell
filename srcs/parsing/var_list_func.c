/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:41:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 17:17:33 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_var	*ft_last_var(t_var *head)
{
	while (head->next)
	{
		head = head->next;
	}
	return (head);
}

void	ft_var_add_back(t_var *new_node, t_var *head)
{
	t_var	*last;

	if (!head)
	{
		head = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		last = ft_last_var(head);
		last->next = new_node;
		new_node->prev = last;
	}
}
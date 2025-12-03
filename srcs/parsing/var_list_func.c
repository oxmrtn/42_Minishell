/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:41:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/08 16:31:32 by mtrullar         ###   ########.fr       */
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

void	ft_var_add_back(t_var *new_node, t_var **head)
{
	t_var	*last;

	if (!(*head))
	{
		*head = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		last = ft_last_var(*head);
		last->next = new_node;
		new_node->prev = last;
		new_node->next = NULL;
	}
}

t_var	*ft_is_var_exist(char *str, t_var *head, int i)
{
	char	*temp;

	if (!str || !head)
		return (NULL);
	temp = ft_strdup_till_i(str, i);
	if (!temp)
		return (NULL);
	while (head)
	{
		if (!ft_ultimate_compare(temp, head->name))
			return (free(temp), head);
		head = head->next;
	}
	free(temp);
	return (NULL);
}

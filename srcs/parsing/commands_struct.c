/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:19:33 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/06 18:32:18 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmds	*ft_get_last_commands(t_cmds *tmp)
{
	t_cmds	*head;

	head = tmp;
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	add_commands(t_cmds *new, t_cmds **head)
{
	t_cmds	*last;

	if (!*head)
	{
		*head = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else
	{
		last = ft_get_last_commands(*head);
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
	return (0);
}

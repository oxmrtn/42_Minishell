/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:20:22 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/07 17:36:28 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_hd	*ft_last_hd(t_hd *head)
{
	while (head->next)
	{
		head = head->next;
	}
	return (head);
}

void	add_back_heredoc_list(t_hd *new_node, t_hd **head)
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
		last = ft_last_hd(*head);
		last->next = new_node;
		new_node->prev = last;
	}
}

int	add_heredoc_list(int fd, t_data *data)
{
	t_hd	*new_node;

	new_node = malloc(sizeof(t_hd));
	if (!new_node)
		return (1);
	new_node->fd = fd;
	add_back_heredoc_list(new_node, data);
}

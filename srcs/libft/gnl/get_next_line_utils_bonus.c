/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:53:05 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 16:40:03 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/get_next_line_bonus.h"

int	ft_line_in_lst(t_gnl_list **node, t_gnl_list **to_del)
{
	t_gnl_list	*current;

	if (!*node)
		return (0);
	current = *node;
	while (current)
	{
		if (current->content == '\n')
		{
			*to_del = current;
			return (1);
		}
		*to_del = current;
		current = current->next;
	}
	return (0);
}

void	ft_lst_add_back(t_gnl_list *new_node, t_gnl_list **current_node)
{
	t_gnl_list	*temp;

	temp = *(current_node);
	if (!temp)
	{
		*current_node = new_node;
	}
	else
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

t_gnl_list	*ft_new_node(char buffer)
{
	t_gnl_list	*new_node;

	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return (NULL);
	new_node->content = buffer;
	new_node->next = NULL;
	return (new_node);
}

void	ft_del_lst(t_gnl_list **node, t_gnl_list **to_del)
{
	t_gnl_list	*next_node;
	t_gnl_list	*current;

	current = *node;
	if (!*node)
		return ;
	next_node = NULL;
	while (current && current != *to_del)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	if (current == *to_del)
	{
		next_node = current->next;
		free(current);
	}
	*node = next_node;
}

t_gnl_list	*ft_lst_last(t_gnl_list *node)
{
	t_gnl_list	*current;

	if (!node)
		return (NULL);
	current = node;
	while (current->next)
		current = current->next;
	return (current);
}

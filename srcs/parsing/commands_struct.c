/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:19:33 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 14:06:59 by mtrullar         ###   ########.fr       */
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

static char	*ft_get_command_name(t_cmds *data)
{
	char		*buffer;
	t_tokens	*current;

	buffer = NULL;
	current = data->tokens;
	while (current)
	{
		buffer = ft_strjoin_s1(buffer, current->str);
		buffer = ft_strjoin_s1(buffer, " ");
		current = current->next;
	}
	return (buffer);
}

int	add_commands(t_cmds *new, t_cmds **head)
{
	t_cmds	*last;

	new->cmd = ft_get_command_name(new);
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

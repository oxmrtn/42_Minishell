/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:25:14 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/30 10:39:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_cmd(t_tokens *actu)
{
	int	result;

	result = 0;
	while (actu && ft_ultimate_compare(actu->str, "|"))
	{
		if (actu->type == CMD)
			result++;
		actu = actu->prev;
	}
	return (result);
}

t_tokens	*ft_get_last_token(t_tokens *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	add_new_token(char *str, t_tokens **head, t_type type)
{
	t_tokens	*new_tokens;
	t_tokens	*last;

	new_tokens = malloc(sizeof(t_tokens));
	if (!new_tokens)
		return (1);
	new_tokens->str = ft_strdup(str);
	new_tokens->type = type;
	if (!new_tokens->str)
		return (1);
	if (!*head)
	{
		*head = new_tokens;
		new_tokens->prev = NULL;
		new_tokens->next = NULL;
	}
	else
	{
		last = ft_get_last_token(*head);
		last->next = new_tokens;
		new_tokens->next = NULL;
		new_tokens->prev = last;
	}
	return (0);
}
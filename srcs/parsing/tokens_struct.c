/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/15 01:08:24 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_tokens_between(char *str, t_tokens *current, t_type type, int i)
{
	t_tokens	*new;
	t_tokens	*temp;

	if (!str || !str[0])
		return (0);
	new = malloc(sizeof(t_tokens));
	if (!new)
		return (1);
	new->type = type;
	new->expand = i;
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(new), 1);
	temp = current->next;
	if (temp)
		temp->prev = new;
	current->next = new;
	new->next = temp;
	new->prev = current;
	return (0);
}

static int	init_ctl(t_tokens **head_node, t_nk *var, char **splitted)
{
	*head_node = NULL;
	var->i = -1;
	splitted = ft_split_quote(line, ' ');
	if (!splitted)
		return (1);
	return (0);
}

t_tokens	*create_token_list(char *line, t_data *data)
{
	t_tokens	*head_node;
	char		**splitted;
	t_nk		var;

	if (init_ctl(&head_node, &var, splitted))
		return (NULL);
	while (splitted[++var.i])
	{
		if (ft_ultimate_len(splitted) == 1)
		{
			var.j = ft_check_variable(splitted[0], data);
			if (var.j == 1)
				return (ft_free_split(splitted), (void *)-1);
			if (var.j == 2)
				return (ft_free_split(splitted), NULL);
		}
		if (add_new_token(splitted[var.i], &head_node, WAIT, 0))
			return (ft_fix(head_node, splitted), NULL);
	}
	var.j = get_type(head_node, data);
	if (var.j == 1)
		return (ft_fix(head_node, splitted), NULL);
	if (var.j == 2)
		return (ft_fix(head_node, splitted), (void *)-1);
	return (ft_free_split(splitted), head_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/16 16:53:56 by ebengtss         ###   ########.fr       */
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

static int	init_ctl(t_tokens **head_node, t_nk *var, char ***s, char *line)
{
	*head_node = NULL;
	var->i = -1;
	*s = ft_split_quote(line, ' ');
	if (!(*s))
		return (1);
	return (0);
}

t_tokens	*create_token_list(char *line, t_data *data)
{
	t_tokens	*head_node;
	char		**spltd;
	t_nk		var;

	if (init_ctl(&head_node, &var, &spltd, line))
		return (NULL);
	while (spltd[++var.i])
	{
		if (ft_ultimate_len(spltd) == 1)
		{
			var.j = ft_check_variable(spltd[0], data);
			if (var.j == 1)
				return (ft_freetab(spltd), data->exit_status = 0, (void *)-1);
			if (var.j == 2)
				return (ft_free_split(spltd), NULL);
		}
		if (add_new_token(spltd[var.i], &head_node, WAIT, 0))
			return (ft_fix(head_node, spltd), NULL);
	}
	var.j = get_type(head_node, data);
	if (var.j == 1)
		return (ft_fix(head_node, spltd), NULL);
	if (var.j == 2)
		return (ft_fix(head_node, spltd), (void *)-1);
	return (ft_free_split(spltd), head_node);
}

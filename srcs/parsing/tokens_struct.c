/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 11:08:06 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_is_pipe(t_tokens *current)
{
	if (!ft_strncmp(current->str, "|", 1))
	{
		if (ft_strlen(current->str) > 1)
			return (current->type = ERROR, 2);
		if (!current->prev)
			return (current->type = ERROR, 2);
		else
		{
			if (current->prev->type == REDIR || current->prev->type == PIPE)
				return (current->type = ERROR, 2);
		}
		if (!current->next)
		{
			current->type = ASK;
			return (2);
		}
		else
		{
			if (!ft_strncmp(current->next->str, "|", 1))
				return (current->type = ERROR, 0);
			else
				return (1);
		}
	}
	return (0);
}

static int	add_tokens_between(char *str, t_tokens *current, t_type type)
{
	t_tokens	*new;
	t_tokens	*temp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (1);
	new->type = type;
	new->str = ft_strdup(str);
	if (!new->str)
		return (1);
	temp = current->next;
	if (temp)
		temp->prev = new;
	current->next = new;
	new->next = temp;
	new->prev = current;
	return (0);
}

static int	commands_shit(t_tokens **node)
{
	t_tokens	*current;
	char		**splitted;
	int			i;

	current = *node;
	if (ft_strchr(current->str, '&') || ft_strchr(current->str, ';')
		|| ft_strchr(current->str, '(') || ft_strchr(current->str, ')'))
		return (current->type = ERROR, 0);
	splitted = ft_split(current->str, ' ');
	if (!splitted)
		return (1);
	if (ft_ultimate_len(splitted) == 1)
	{
		if (current->type != ENV)
			current->type = CMD;
		return (ft_free_split(splitted), 0);
	}
	i = 0;
	free(current->str);
	current->str = ft_strdup(splitted[0]);
	if (!current->str)
		return (1);
	current->type = CMD;
	while (splitted[++i])
	{
		add_tokens_between(splitted[i], current, ARGS);
		current = current->next;
	}
	return (*node = current, ft_free_split(splitted), 0);
}

int	get_type(t_tokens *head)
{
	t_tokens	*current;

	current = head;
	while (current)
	{
		if (ft_is_redirect_sign(current))
		{
			if (current->type != ERROR)
				current->type = REDIR;
		}
		else if (ft_is_commands(current))
		{
			if (commands_shit(&current))
				return (1);
		}
		else if (ft_is_pipe(current) != 0)
		{
			if (current->type != ASK && current->type != ERROR)
				current->type = PIPE;
		}
		else if (ft_is_args(current))
			current->type = ARGS;
		current = current->next;
	}
	return (0);
}

t_tokens	*create_token_list(char *line, t_data *data)
{
	t_tokens	*head_node;
	char		**splitted;
	int			i;
	char		*temp;

	head_node = NULL;
	i = -1;
	splitted = ft_split_quote(line, ' ');
	if (!splitted)
		return (NULL);
	while (splitted[++i])
	{
		if (ft_ultimate_len(splitted) == 1)
			if (ft_check_variable(splitted[0], data))
				return (ft_free_split(splitted), NULL);
		temp = ft_flat_string(splitted[i], data);
		if (!temp)
			return (ft_freetab(splitted), NULL);
		if (add_new_token(temp, &head_node, WAIT))
			return (ft_freetab(splitted), free(temp), NULL);
		free(temp);
	}
	if (get_type(head_node))
		return (ft_freetab(splitted), NULL);
	return (ft_freetab(splitted), head_node);
}

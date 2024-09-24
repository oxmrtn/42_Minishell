/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/24 14:42:36 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_is_pipe(t_tokens *current)
{
	if (ft_strncmp(current->str, "|", 1) == 0)
	{
		if (!current->next)
		{
			current->type = ASK;
			return (2);
		}
		else
			return (1);
	}
	else
		return (0);
}

void	get_type(t_tokens *head)
{
	t_tokens	*current;

	current = head;
	while (current)
	{
		if (ft_is_commands(current))
		{
			if (current->type != ENV)
				current->type = CMD;
		}
		else if (ft_is_redirect_sign(current))
		{
			if (current->type != ERROR)
				current->type = REDIR;
		}
		else if (ft_is_pipe(current) != 0)
		{
			if (current->type != ASK)
				current->type = PIPE;
		}
		else if (ft_is_args(current))
			current->type = ARGS;
		current = current->next;
	}
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

t_tokens	*create_token_list(char *line, t_data *data)
{
	t_tokens	*head_node;
	char		**splitted;
	char		*temp;
	int			i;

	head_node = NULL;
	i = 0;
	splitted = ft_split_quote(line, ' ');
	if (!splitted)
		return (NULL);
	while (splitted[i])
	{
		if (ft_ultimate_len(splitted) == 1)
			if (ft_check_variable(splitted[0], data))
				return (ft_free_split(splitted), NULL);
		temp = ft_flat_string(splitted[i], data);
		if (!temp)
			return (ft_freetab(splitted), NULL);
		if (add_new_token(temp, &head_node, WAIT) == 1)
			return (NULL);
		free(temp);
		i++;
	}
	get_type(head_node);
	return (ft_freetab(splitted), head_node);
}

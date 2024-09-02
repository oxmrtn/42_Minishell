/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/02 14:29:53 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmds	*ft_get_last_commands(t_cmds *tmp)
{
	t_cmds *head;

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

t_type	get_type(char *str, int i, char **splitted)
{
	if (str[0] == '-')
		return (ARGS);
	else if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (REDIR_IN);
	else if (i > 0)
		return (ARGS);
	else
		return (CMD);
}

t_tokens	*ft_get_last_token(t_tokens *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	add_new_token(char *str, t_tokens **head, int i, char **splitted)
{
	t_tokens	*new_tokens;
	t_tokens	*last;

	new_tokens = malloc(sizeof(t_tokens));
	if (!new_tokens)
		return (1);
	new_tokens->str = ft_strdup(str);
	if (!new_tokens->str)
		return (1);
	new_tokens->type = get_type(str, i, splitted);
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

t_tokens	*create_token_list(char *line)
{
	t_tokens	*head_node;
	char		**splitted;
	int			i;

	head_node = NULL;
	i = 0;
	splitted = ft_split(line, ' ');
	if (!splitted)
		return (NULL);
	while (splitted[i])
	{
		if (add_new_token(splitted[i], &head_node, i, splitted) == 1)
			return (NULL);
		i++;
	}
	ft_freetab(splitted);
	return (head_node);
}

int	ft_parser(char *line, t_cmds **commands)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds));
	if (!new_node)
		return (1);
	new_node->tokens = create_token_list(line);
	new_node->cmd = ft_strdup(line);
	if (!new_node->cmd || !new_node->tokens)
		return (1);
	if (add_commands(new_node, commands) == 1)
		return (printf("fail ici\n"), 1);
	return (0);
}

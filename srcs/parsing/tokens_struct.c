/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/10 23:42:11 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	add_tokens_between(char *str, t_tokens *current, t_type type)
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

static int	commands_shit(t_tokens *current)
{
	if (ft_strchr(current->str, '&') || ft_strchr(current->str, ';')
		|| ft_strchr(current->str, '(') || ft_strchr(current->str, ')'))
		return (current->type = ERROR, 0);
	if (!current->str)
		return (1);
	current->type = CMD;
	return (0);
}

int	ft_expand(t_tokens *head, t_data *data, int *flag)
{
	char	*temp;
	
	temp = NULL;
	if (!head->str)
		return (1);
	if (!head->str[0])
		return (0);
	temp = ft_flat_string(head->str, data, flag);	
	if (!temp)
		return (1);
	free(head->str);
	head->str = temp;
	return (0);
}

void	add_chain_between(t_tokens *head, t_tokens *chain)
{
	if (head->prev)
		head->prev->next = chain;
	if (head->next)
		head->next->prev = ft_get_last_token(chain);
	chain->next = head->next;
	head->prev = chain;
	chain->prev = head;
}

int	flag_on(t_tokens *head)
{
	t_tokens	*tmp;
	char		**splitted;
	int			i;

	i = 0;
	splitted = ft_split(head->str, ' ');
	if (!splitted)
		return (1);
	tmp = malloc(sizeof(t_tokens));
	if (!tmp)
		return (1);
	while (splitted[i])
	{
		add_new_token(splitted[i], &tmp, WAIT);
		i++;
	}
	add_chain_between(head, tmp);
	return (0);	
}

int	get_type_bis(t_tokens *current)
{
	if (ft_is_redirect_sign(current))
		{
			if (current->type != ERROR)
				current->type = REDIR;
		}
		else if (ft_is_commands(current))
		{
			if (commands_shit(current))
				return (1);
		}
		else if (ft_is_pipe(current) != 0)
		{
			if (current->type != ASK && current->type != ERROR)
				current->type = PIPE;
		}
		else if (ft_is_args(current))
			current->type = ARGS;
		return (0);
}

int	get_type(t_tokens *head, t_data *data)
{
	t_tokens	*current;
	int			flag;
	
	current = head;
	while (current)
	{
		flag = 0;
		if (ft_expand(current, data, &flag))
			return (1);
		if (flag == 1)
		{
			flag_on(current);
		}
		if (get_type_bis(current))
			return (1);
		current = current->next;
	}
	return (0);
}

t_tokens	*create_token_list(char *line, t_data *data)
{
	t_tokens	*head_node;
	char		**splitted;
	int			i;

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
		if (add_new_token(splitted[i], &head_node, WAIT))
			return (ft_fix(head_node, splitted), NULL);
	}
	if (get_type(head_node, data))
		return (ft_fix(head_node, splitted), NULL);
	return (ft_free_split(splitted), head_node);
}

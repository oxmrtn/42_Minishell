/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:30:23 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 16:00:29 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	commands_shit(t_tokens *current)
{
	if (ft_strchr(current->str, '&') || ft_strchr(current->str, ';')
		|| ft_strchr(current->str, '(') || ft_strchr(current->str, ')'))
		return (current->type = ERROR, 0);
	if (!current->str)
		return (1);
	if (current->type != ENV)
		current->type = CMD;
	return (0);
}

static int	ft_expand(t_tokens *head, t_data *data, int *flag)
{
	char	*temp;

	temp = NULL;
	if (!head->str)
		return (1);
	if (!head->str[0])
		return (0);
	temp = ft_flat_string(head->str, data, flag, head);
	if (!temp)
		return (1);
	free(head->str);
	head->str = temp;
	return (0);
}

static int	flag_on(t_tokens *head)
{
	char		**splitted;
	int			i;

	if (!head->str || (head->str && !head->str[0]))
		return (0);
	splitted = ft_split(head->str, ' ');
	if (!splitted)
		return (1);
	free(head->str);
	head->str = ft_strdup(splitted[0]);
	if (!head->str)
		return (ft_free_split(splitted), 1);
	i = ft_ultimate_len(splitted) - 1;
	while (i >= 1)
	{
		add_tokens_between(splitted[i], head, WAIT, 1);
		i--;
	}
	ft_free_split(splitted);
	return (0);
}

static int	get_type_bis(t_tokens *current)
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
		if (ft_cqs(current->str))
			return (2);
		if (current->expand == 0)
			if (ft_expand(current, data, &flag))
				return (1);
		if (flag == 1)
			flag_on(current);
		if (current->expand <= 1)
			if (split_redir(current))
				return (1);
		if (!current->str || (current->str && !current->str[0]))
			current->type = NO_TYPE;
		else if (get_type_bis(current))
			return (1);
		current = current->next;
	}
	return (0);
}

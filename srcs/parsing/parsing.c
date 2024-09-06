/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/06 14:19:42 by ebengtss         ###   ########.fr       */
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

int	ft_test_path(t_tokens *node, t_data *data)
{
	t_env	*env;
	char	**path;
	int		i;
	char	*temp;

	i = 0;
	env = data->envs->env;
	while (env)
	{
		if (ft_strncmp(env->content, "PATH=", 5) == 0)
		{
			path = ft_split(&env->content[5], ':');
			if (!path)
				return (0);
			while (path[i])
			{
				temp = ft_strjoin_c(path[i++], node->str, '/', 0);
				if (access(temp, X_OK) == 0)
				{
					free(node->str);
					node->str = ft_strdup(temp);
					return (free(temp), ft_free_split(path), 1);
				}
				free(temp);
			}
		}
		env = env->next;
	}
	return (0);
}

int	ft_is_commands(t_tokens *node, t_data *data)
{
	return (is_builtin(node->str) || ft_test_path(node, data));
}

int	ft_is_args(t_tokens *node)
{
	if (node->prev == NULL)
		return (0);
	return (node->prev->type == ARGS || node->prev->type == CMD);
}

int	ft_is_redirect_sign(t_tokens *current)
{
	if (ft_strncmp(current->str, "|", 1) == 0)
		current->type = PIPE;
	else if (!ft_strncmp(current->str, ">", 1))
	{
		if (current->next)
			current->next->type = OUTFILE;
		else
			current->type = ERROR;
	}
	else if (!ft_strncmp(current->str, ">>", 2))
	{
		if (current->next)
			current->next->type = APPEND;
		else
			current->type = ERROR;
	}
	else if (!ft_strncmp(current->str, "<<", 2))
	{
		if (current->next)
			current->next->type = LIMITER;
		else
			current->type = ERROR;
	}
	else if (!ft_strncmp(current->str, "<", 1))
	{
		if (current->prev)
			current->prev->type = INFILE;
		else
			current->type = ERROR;
	}
	return (0);
}

void	get_type(t_tokens *head, t_data *data)
{
	int			i;
	t_tokens	*current;

	i = 0;
	current = head;
	while (current)
	{
		if (ft_is_commands(current, data))
			current->type = CMD;
		ft_is_redirect_sign(current);
		if (current->type == WAIT)
		{
			if (!ft_is_args(current))
				current->type = NO_TYPE;
			else
				current->type = ARGS;
		}
		current = current->next;
		i++;
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

int	add_new_token(char *str, t_tokens **head)
{
	t_tokens	*new_tokens;
	t_tokens	*last;

	new_tokens = malloc(sizeof(t_tokens));
	if (!new_tokens)
		return (1);
	new_tokens->str = ft_strdup(str);
	new_tokens->type = WAIT;
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
	int			i;

	head_node = NULL;
	i = 0;
	splitted = ft_split(line, ' ');
	if (!splitted)
		return (NULL);
	while (splitted[i])
	{
		if (add_new_token(splitted[i], &head_node) == 1)
			return (NULL);
		i++;
	}
	get_type(head_node, data);
	ft_freetab(splitted);
	return (head_node);
}

int	ft_parser(char *line, t_cmds **commands, t_data *data)
{
	t_cmds	*new_node;

	if (ft_is_variable_declaration(line) == 0)
	{
		if (!ft_add_variable(line, data))
			return (1);
	}
	else
	{
		new_node = malloc(sizeof(t_cmds));
		if (!new_node)
			return (1);
		new_node->tokens = create_token_list(line, data);
		if (!new_node->tokens)
			return (1);
		new_node->cmd = ft_strdup(line);
		if (!new_node->cmd)
			return (1); // ADD FREE_TOKEN
		if (add_commands(new_node, commands) == 1)
			return (1);
	}
	return (0);
}

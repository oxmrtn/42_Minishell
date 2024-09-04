/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 14:57:51 by mtrullar         ###   ########.fr       */
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
	env = data->env;
	while (env)
	{
		if (!ft_strncmp(env->content, "PATH=", 5))
		{
			path = ft_split(&env->content[5], ':');
			if (!path)
				return (0);
			while (path[i])
			{
				temp = ft_strjoin(path[i++], node->str);
				if (access(temp, X_OK))
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

int	ft_is_args(char **splitted, int i, t_data *data)
{
	int j;
	int	find;

	find = 0;
	j = i;
	while (j > 0)
	{
		if (!ft_strncmp(splitted[j], "|", 1))
		{
			find = 1;
		}
		if (ft_is_commands(splitted[j], data))
		{
			if (find == 1)
				return (0);
			else
				return (1);
		}
		j--;
	}
	return (0);
}

int	ft_is_redirect_sign(char **splitted, int i, t_tokens *current)
{
	if (!ft_strncmp(current->str, "|", 1))
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

void	get_type(t_tokens *head, char **splitted, t_data *data)
{
	int			i;
	t_tokens	*current;

	i = 0;
	current = head;
	while (current)
	{
		if (ft_is_commands(current, data))
			current->type = CMD;
		else if (ft_is_args(splitted, i, data))
			current->type = ARGS;
		else if (ft_is_redirect_sign(splitted, i, current))
			continue;
		else
			current->type = NO_TYPE;
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
		if (add_new_token(&head_node, i) == 1)
			return (NULL);
		i++;
	}
	get_type(head_node, splitted, data);
	ft_freetab(splitted);
	return (head_node);
}

int	ft_parser(char *line, t_cmds **commands, t_data *data)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds));
	if (!new_node)
		return (1);
	new_node->tokens = create_token_list(line, data);
	new_node->cmd = ft_strdup(line);
	if (!new_node->cmd || !new_node->tokens)
		return (1);
	if (add_commands(new_node, commands) == 1)
		return (printf("fail ici\n"), 1);
	return (0);
}

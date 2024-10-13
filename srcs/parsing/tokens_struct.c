/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:21:38 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/14 00:25:46 by mtrullar         ###   ########.fr       */
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
	printf("NODE CREATED = %s", new->str);
	if (new->next)
		printf("NEXT NODE = %s", new->next->str);
	if (new->prev)
		printf("PREV NODE = %s", new->prev->str);
	printf("\n");
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

int	flag_on(t_tokens *head)
{
	char		**splitted;
	int			i;

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

static int	handle_redir_bis(t_tokens *current, char c, int *i, char *str)
{
	char	tmp[3];

	if (c == '>')
		ft_strlcpy(tmp, ">>", 3);
	else if (c == '<')
		ft_strlcpy(tmp, "<<", 3);
	else
		ft_strlcpy(tmp, "||", 3);
	if (c == '>' || c == '<')
	{
		if ((*i) - 1 >= 0 && str[(*i) - 1] == c)
		{
			if (add_tokens_between((str + *i + 1), current, WAIT, 3)
				|| add_tokens_between(tmp, current, WAIT, 3))
				return (1);
			(*i)--;
		}
		else if (add_tokens_between((str + *i + 1), current, WAIT, 3)
			|| add_tokens_between((tmp + 1), current, WAIT, 3))
			return (1);
	}
	if (c == '|' && (add_tokens_between((str + *i + 1), current, WAIT, 3)
		|| add_tokens_between((tmp + 1), current, WAIT, 3)))
		return (1);
	return (0);
}

void	delete_node(t_tokens *current)
{
	if (!current)
		return ;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(current->str);
	free(current);
}

int	handle_redir(t_tokens *current)
{
	char	*str;
	int		i;
	int		k;

	k = -1;
	i = ft_strlen(current->str) - 1;
	str = current->str;
	while (i >= 0)
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			if (handle_redir_bis(current, str[i], &i, str))
				return (1);
			k = i;
		}
		i--;
	}
	if (k == 0)
	{
		t_tokens *temp = current->next;
		delete_node(current);
		current = temp;
	}
	else if (k != -1)
	{
		char *temp = ft_strdup_till_i(current->str, k);
		free(current->str);
		current->str = temp;
	}
	t_tokens	*t = current;
	while (t)
	{
		printf("hr %s\n", t->str);
		t = t->next;
		sleep(5);
	}
	return (0);
}

int	get_type(t_tokens *head, t_data *data)
{
	t_tokens	*current;
	int			flag;
	
	current = head;
	while (current)
	{
		printf("GT NODE = %s | EXPAND = %d \n", current->str, current->expand);
		flag = 0;
		if (current->expand == 0 && current->type != LIMITER)
		{
			if (ft_expand(current, data, &flag))
				return (1);	
		}
		if (flag == 1)
			flag_on(current);
		if (current->expand <= 1)
			if (handle_redir(current))
				return (1);
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
		if (add_new_token(splitted[i], &head_node, WAIT, 0))
			return (ft_fix(head_node, splitted), NULL);
	}
	if (get_type(head_node, data))
		return (ft_fix(head_node, splitted), NULL);
	return (ft_free_split(splitted), head_node);
}

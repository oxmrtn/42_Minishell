/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/09 14:26:53 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_is_variable_declaration(char *str)
{
	int	i;
	int	equal_count;

	equal_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		else if (str[i] == '=')
			equal_count++;
		i++;
	}
	if (equal_count >= 1)
		return (0);
	return (1);
}

int	ft_add_variable(char *str, t_data *data)
{
	t_var	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return (1);
	while (str[i] != '=')
		i++;
	new_node->name = ft_strdup_till_i(str, i);
	if (!new_node->name)
		return (free(new_node), 1);
	new_node->content = ft_strdup(str + i + 1);
	if (!new_node->content)
	{
		free(new_node->name);
		return (free(new_node), 1);
	}
	ft_var_add_back(new_node, &data->var);
	return (0);
}

char	*ft_get_variable_value(char *key, t_data *data)
{
	t_var	*current;

	current = data->var;
	printf("temp = %s\n", key);
	if (!key || !current)
		return (NULL);
	while (current && ft_strncmp(key + 1, current->name, ft_strlen(current->name)))
	{
		printf("current->name = %s\n", current->name);
		current = current->next;
	}
	if (current)
		return (ft_strdup(current->content));
	else
		return (ft_strdup("\n"));
}

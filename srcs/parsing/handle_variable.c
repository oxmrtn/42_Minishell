/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 11:22:12 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_check_variable(char *str, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[0] == 34 || str[0] == 39)
		return (1);
	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (1);
	if (env_update(data->envs->env, str))
		return (0);
	if (ft_add_variable(str, data))
		return (0);
	return (1);
}

int	ft_add_variable(char *str, t_data *data)
{
	t_var	*new_node;
	int		i;
	char	*temp;

	temp = ft_strchr(str, '=');
	i = 0;
	new_node = ft_is_var_exist(str, data->var, i);
	if (new_node)
	{
		free(new_node->content);
		new_node->content = ft_strdup(temp + 1);
		return (0);
	}
	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return (1);
	new_node->name = ft_strdup_till_i(str, i);
	if (!new_node->name)
		return (free(new_node), 1);
	new_node->content = ft_strdup(temp + 1);
	if (!new_node->content)
		return (free(new_node->name), free(new_node), 1);
	ft_var_add_back(new_node, &data->var);
	return (0);
}

char	*ft_get_variable_value(char *key, t_data *data)
{
	t_var	*current;
	t_env	*env;

	env = data->envs->env;
	current = data->var;
	if (!key || !current)
		return (NULL);
	while (current && ft_ultimate_compare(key, current->name))
	{
		current = current->next;
	}
	if (current)
		return (ft_strdup(current->content));
	else
	{
		while (env && ft_ultimate_compare(key, current->name))
		{
			env = env->next;
		}
		if (env)
			return (ft_strdup(current->content));
		else
			return (ft_strdup(""));
	}
}

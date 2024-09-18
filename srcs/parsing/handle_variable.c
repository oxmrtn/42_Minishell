/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/18 09:40:01 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_check_variable(char *str, t_data *data)
{
	char	*tmp;
	char	*t1;
	char	*t2;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (0);
	t1 = ft_strchr(str, 34);
	t2 = ft_strchr(str, 39);
	if ((t1 && tmp > t1) || (t2 && tmp > t2))
		return (0);
	if (ft_check_quote_syntax(tmp + 1))
		return (0);
	if (env_update(data->envs->env, str))
		return (1);
	if (!ft_add_variable(str, data))
		return (1);
	return (0);
}

int	ft_add_variable(char *str, t_data *data)
{
	t_var	*new_node;
	int		i;

	i = ft_strchr(str, '=') - str;
	new_node = ft_is_var_exist(str, data->var, i);
	if (new_node)
	{
		free(new_node->content);
		new_node->content = ft_strdup_custom(str + i + 1);
		if (!new_node->content)
			return (free(new_node), 0);
		return (0);
	}
	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return (1);
	new_node->name = ft_strdup_till_i(str, i);
	if (!new_node->name)
		return (free(new_node), 1);
	new_node->content = ft_strdup_custom(str + i + 1);
	if (!new_node->content)
		return (free(new_node->name), free(new_node), 1);
	return (ft_var_add_back(new_node, &data->var), 0);
}

char	*ft_get_variable_value(char *key, t_data *data)
{
	t_var	*current;
	t_env	*env;

	env = data->envs->env;
	current = data->var;
	if (!key || !current)
		return (NULL);
	while ((current && current->content && current->name))
	{
		if (!ft_ultimate_compare(key, current->name))
			return (ft_strdup(current->content));
		current = current->next;
	}
	while (env && env->val)
	{
		if (!ft_ultimate_compare(key, env->key))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (ft_strdup(""));
}

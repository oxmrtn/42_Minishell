/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/08 16:16:28 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	check_is_correct_var(char *equal, char *str)
{
	if (!equal)
		return (1);
	if (!ft_strncmp(str, "_", equal - str))
		return (1);
	while (str != equal)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_check_variable(char *str, t_data *data)
{
	char	*tmp;
	char	*t1;
	char	*t2;

	tmp = ft_strchr(str, '=');
	if (check_is_correct_var(tmp, str))
		return (0);
	t1 = ft_strchr(str, 34);
	t2 = ft_strchr(str, 39);
	if ((t1 && tmp > t1) || (t2 && tmp > t2) || ft_check_quote_syntax(tmp + 1))
		return (0);
	if (is_inenv_str(data->envs->env, str))
	{
		env_update(data->envs->exp, str);
		env_update(data->envs->env, str);
		return (envtab_update(data), 1);
	}
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
			return (free(new_node), 1);
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

int	ft_update_variable(char *key, char *val, t_data *data)
{
	t_var	*node;

	node = data->var;
	while (node && ft_ultimate_compare(key, node->name))
		node = node->next;
	if (!node)
		return (0);
	if (node->content)
		free(node->content);
	node->content = ft_strdup(val);
	if (!node->content)
		return (1);
	return (0);
}

char	*ft_get_variable_value(char *key, t_data *data)
{
	t_var	*current;
	t_env	*env;

	env = data->envs->env;
	current = data->var;
	if (!key)
		return (NULL);
	while (env && env->val && env->key)
	{
		if (!ft_ultimate_compare(key, env->key))
			return (ft_strdup(env->val));
		env = env->next;
	}
	while ((current && current->content && current->name))
	{
		if (!ft_ultimate_compare(key, current->name))
			return (ft_strdup(current->content));
		current = current->next;
	}
	return (ft_strdup(""));
}

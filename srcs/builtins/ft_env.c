/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/18 14:20:31 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	if (env_update(data->envs->env, cmdve))
		return (0);
	node = envnew_gtw(cmdve, 0);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->l_env, node);
	return (0);
}

void	tmp_env_clean(t_data *data)
{
	t_env	*l_node;

	l_node = data->envs->l_env;
	ft_free_env(&l_node->next);
	data->envs->l_env->next = NULL;
}

void	print_env(t_env *env, int env_or_exp)
{
	while (env)
	{
		if (!env_or_exp)
		{
			if (env->val)
				printf("%s=%s\n", env->key, env->val);
			else if (ft_ultimate_compare(env->key, "=") != 0)
				printf("%s=\n", env->key);
			else
				printf("%s\n", env->key);
		}
		else
		{
			if (env->exp_noval == 1)
				printf("%s\n", env->key);
			else if (env->val)
				printf("%s=\"%s\"\n", env->key, env->val);
			else
				printf("%s=\"\"\n", env->key);
		}
		env = env->next;
	}
}

char	**env_to_tab(t_data *data)
{
	size_t	i;
	size_t	size;
	t_env	*env;
	char	**tmp_env;

	i = 0;
	env = data->envs->env;
	size = ft_envsize(env);
	tmp_env = malloc(sizeof(char *) * (size + 1));
	if (!tmp_env)
		return (NULL);
	tmp_env[size] = NULL;
	while (env)
	{
		if (env->val)
			tmp_env[i] = ft_strjoin_c(env->key, env->val, '=', 0);
		else if (ft_ultimate_compare(env->key, "=") != 0)
			tmp_env[i] = ft_strjoin(env->key, "=");
		else
			tmp_env[i] = ft_strdup("=");
		if (!tmp_env[i++])
			return (NULL);
		env = env->next;
	}
	return (tmp_env);
}

int	ft_env(t_data *data, char **cmdve)
{
	size_t	i;

	i = 1;
	while (cmdve[i])
	{
		if (tmp_env_add(data, cmdve[i]))
			return (tmp_env_clean(data), -100);
		i++;
	}
	print_env(data->envs->env, 0);
	tmp_env_clean(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/12 15:03:26 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	node = envnew_gtw(cmdve, 0);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->l_env, node);
	return (0);
}

static void	env_clean(t_data *data)
{
	t_env	*l_node;

	l_node = data->envs->l_env;
	while (l_node->next)
		ft_envdelone(data, l_node->next, 1);
}

void	print_env(t_env *env, int env_or_exp)
{
	while (env)
	{
		if (!env_or_exp)
			printf("%s=%s\n", env->key, env->val);
		else
		{
			if (env->exp_noval == 1)
				printf("%s\n", env->key);
			else
				printf("%s=\"%s\"\n", env->key, env->val);
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
		tmp_env[i] = ft_strjoin_c(env->key, env->val, '=', 0);
		if (!tmp_env[i])
			return (NULL);
		env = env->next;
		i++;
	}
	return (tmp_env);
}

int	ft_env(t_data *data, char **cmdve)
{
	size_t	i;

	i = 1;
	while (cmdve[i])
	{
		if (!strchr(cmdve[i], '='))
		{
			data->envs->tmpenv = env_to_tab(data);
			if (!data->envs->tmpenv)
				return (1);
			// exec
			free(data->envs->tmpenv);
			data->envs->tmpenv = NULL;
			return (env_clean(data), 0);
		}
		else
			if (tmp_env_add(data, cmdve[i]))
				return (env_clean(data), 1);
		i++;
	}
	print_env(data->envs->env, 0);
	env_clean(data);
	return (0);
}

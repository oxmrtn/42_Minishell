/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:45:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/25 14:23:44 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	add_min_env2(t_data *data, char *defkey, char *defval, int is_exp)
{
	t_env	**env;
	t_env	*entry;
	char	*key;
	char	*val;

	if (!is_exp)
		env = &data->envs->env;
	else
		env = &data->envs->exp;
	key = ft_strdup(defkey);
	val = ft_strdup(defval);
	if (!key || !val)
		return (1);
	entry = ft_envnew(key, val, 0);
	if (!entry)
		return (1);
	if (data->envs->l_env && !is_exp)
		ft_envadd_front(&data->envs->l_env, entry);
	else if ((!data->envs->l_env && !is_exp) || is_exp)
		ft_envadd_back(env, entry);
	return (0);
}

static int	add_min_env(t_data *data, char *defkey, char *defval, int is_exp)
{
	if (add_min_env2(data, defkey, defval, 0))
		return (1);
	if (is_exp)
		if (add_min_env2(data, defkey, defval, 1))
			return (1);
	if (!is_exp)
		data->envs->l_env = ft_envlast(data->envs->env);
	return (0);
}

static int	is_in_env(t_data *data, char *keycheck)
{
	t_env	*env;

	env = data->envs->env;
	while (env)
	{
		if (!ft_ultimate_compare(env->key, keycheck))
			return (0);
		env = env->next;
	}
	return (1);
}

static int	incr_shlvl(t_data *data)
{
	t_env	*env;
	t_env	*exp;
	char	*newval;
	char	*incrval;

	env = data->envs->env;
	while (env)
	{
		if (!ft_ultimate_compare(env->key, "SHLVL"))
		{
			incrval = ft_itoa(ft_atoi(env->val) + 1);
			newval = ft_strjoin_c(env->key, incrval, '=', 2);
			if (!newval)
				return (1);
		}
		env = env->next;
	}
	env = data->envs->env;
	exp = data->envs->exp;
	env_update(env, newval);
	env_update(exp, newval);
	free(newval);
	return (0);
}

int	check_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (1);
	if (is_in_env(data, "PWD"))
		if (add_min_env(data, "PWD", pwd, 1))
			return (1);
	free(pwd);
	if (is_in_env(data, "SHLVL"))
	{
		if (add_min_env(data, "SHLVL", "1", 1))
			return (1);
	}
	else
		if (incr_shlvl(data))
			return (1);
	if (is_in_env(data, "_"))
		if (add_min_env(data, "_", "/usr/bin/env", 0))
			return (1);
	return (0);
}

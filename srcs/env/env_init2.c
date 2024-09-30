/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:45:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/30 14:22:33 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_inenv_key(t_env *env, char *keycheck)
{
	while (env)
	{
		if (!ft_ultimate_compare(env->key, keycheck))
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_inenv_str(t_env *env, char *strcheck)
{
	size_t	i;
	size_t	maxlen;

	i = 0;
	while (strcheck[i] && strcheck[i] != '+' && strcheck[i] != '=')
		i++;
	while (env)
	{
		maxlen = ft_max(ft_strlen(env->key), i);
		if (!ft_strncmp(env->key, strcheck, maxlen))
			return (1);
		env = env->next;
	}
	return (0);
}

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

int	check_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (1);
	if (!is_inenv_key(data->envs->env, "PWD"))
		if (add_min_env(data, "PWD", pwd, 1))
			return (1);
	free(pwd);
	if (!is_inenv_key(data->envs->env, "SHLVL"))
	{
		if (add_min_env(data, "SHLVL", "1", 1))
			return (1);
	}
	else
		if (incr_shlvl(data))
			return (1);
	if (!is_inenv_key(data->envs->env, "_"))
		if (add_min_env(data, "_", "/usr/bin/env", 0))
			return (1);
	return (0);
}

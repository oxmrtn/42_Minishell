/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:45:52 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/24 18:30:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*envnew_gtw(char *str, int is_exp_no_val)
{
	char	*key;
	char	*val;
	char	*c;
	size_t	i;

	i = 0;
	c = ft_strchr(str, '=');
	if (!c && !is_exp_no_val)
		return (NULL);
	while (str[i] && &str[i] != c)
		i++;
	if (str[0] == '=' && i == 1)
		key = ft_strdup("=");
	else
		key = ft_strdup_till_i(str, i);
	if (c && c[1])
		val = ft_strdup(&c[1]);
	else
		val = NULL;
	return (ft_envnew(key, val, is_exp_no_val));
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
		ft_envadd_front(env, entry);
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
			incrval = ft_atoi(env->key) + 1;
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
	if (is_in_env(data, "SHLVL"))
	{
		if (add_min_env(data, "SHLVL", "1", 1))
			return (1);
	}
	if (is_in_env(data, "_"))
		if (add_min_env(data, "_", "/usr/bin/env", 0))
			return (1);
	return (0);
}

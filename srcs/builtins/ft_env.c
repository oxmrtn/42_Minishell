/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/30 14:19:13 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	isvalid_env(char *str, int only_key)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && only_key)
			return (1);
		if (!i && (ft_isdigit(str[i]) || str[i] == '='))
			return (1);
		if (!only_key && (str[i] == '='
				|| (str[i] == '+' && str[i + 1] == '=')))
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

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
	while (str[i] && str[i] != '+' && &str[i] != c)
		i++;
	if (str[0] == '=' && !i)
		key = ft_strdup("=");
	else
		key = ft_strdup_till_i(str, i);
	if (c && c[1])
		val = ft_strdup(&c[1]);
	else
		val = NULL;
	return (ft_envnew(key, val, is_exp_no_val));
}

void	print_env(t_env *env, int env_or_exp)
{
	while (env)
	{
		if (!env_or_exp)
		{
			if (env->val && !ft_ultimate_compare(env->key, "="))
				printf("%s%s\n", env->key, env->val);
			else if (!env->val && !ft_ultimate_compare(env->key, "="))
				printf("%s\n", env->key);
			else if (env->val)
				printf("%s=%s\n", env->key, env->val);
			else
				printf("%s=\n", env->key);
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

char	**env_to_tab(t_env *env)
{
	size_t	i;
	size_t	size;
	char	**tmp_env;

	i = 0;
	size = ft_envsize(env);
	tmp_env = malloc(sizeof(char *) * (size + 1));
	if (!tmp_env)
		return (NULL);
	tmp_env[size] = NULL;
	while (env)
	{
		if (ft_ultimate_compare(env->key, "=") != 0)
		{
			if (env->val)
				tmp_env[i] = ft_strjoin_c(env->key, env->val, '=', 0);
			else
				tmp_env[i] = ft_strjoin(env->key, "=");
			if (!tmp_env[i++])
				return (NULL);
		}
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
		if (ft_strncmp(cmdve[i], "_=", 2) != 0
			&& ft_strncmp(cmdve[i], "_+=", 3) != 0)
			if (tmp_env_add(data, cmdve[i]))
				return (-100);
		i++;
	}
	if (i == 1)
		print_env(data->envs->env, 0);
	else
	{
		print_env(data->envs->tmpenv, 0);
		ft_free_env(&data->envs->tmpenv);
		data->envs->tmpenv = NULL;
	}
	return (0);
}

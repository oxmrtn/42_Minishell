/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/26 14:47:53 by ebengtss         ###   ########.fr       */
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

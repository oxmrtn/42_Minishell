/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:29 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 18:02:00 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	print_env(t_env *env)
{
	int	retval;

	retval = 0;
	while (env)
	{
		if (env->hidden)
			retval = 0;
		else if (env->val && !ft_ultimate_compare(env->key, "="))
			retval = printf("%s%s\n", env->key, env->val);
		else if (!env->val && !ft_ultimate_compare(env->key, "="))
			retval = printf("%s\n", env->key);
		else if (env->val)
			retval = printf("%s=%s\n", env->key, env->val);
		else
			retval = printf("%s=\n", env->key);
		if (retval < 0)
		{
			ft_puterror("minishell: 'env': write error: ");
			perror(NULL);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

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
		if (ft_ultimate_compare(env->key, "=") != 0 && !env->hidden)
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
	int		retval;

	i = 1;
	retval = 0;
	if (data->envs->direrr && !is_inenv_key(data->envs->env, "PWD"))
		ft_puterror(
			"job-working-directory: error retrieving current directory\n");
	while (cmdve[i])
	{
		if (cmdve[i][0] && ft_strncmp(cmdve[i], "_=", 2) != 0
			&& ft_strncmp(cmdve[i], "_+=", 3) != 0)
			if (tmp_env_add(data, cmdve[i]))
				return (-100);
		i++;
	}
	if (i == 1)
		retval = print_env(data->envs->env);
	else
	{
		retval = print_env(data->envs->tmpenv);
		ft_free_env(&data->envs->tmpenv);
		data->envs->tmpenv = NULL;
	}
	return (retval);
}

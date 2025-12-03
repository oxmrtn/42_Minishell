/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:13:16 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 19:56:29 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	set_hidden(t_env *env, char *keycheck)
{
	while (env)
	{
		if (!ft_ultimate_compare(env->key, keycheck))
		{
			env->hidden = 1;
			return ;
		}
		env = env->next;
	}
}

int	check_env2(t_data *data)
{
	char	*paths;

	if (!is_inenv_key(data->envs->exp, "OLDPWD"))
		if (expenv_add2(data, "OLDPWD", 1))
			return (1);
	if (is_inenv_key(data->envs->env, "PATH"))
		return (0);
	paths = ft_strjoin("/usr/local/sbin:/usr/local/bin:",
			"/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin");
	if (!paths)
		return (1);
	if (add_min_env(data, "PATH", paths, 1))
		return (free(paths), 1);
	free(paths);
	set_hidden(data->envs->env, "PATH");
	set_hidden(data->envs->exp, "PATH");
	return (0);
}

static char	*incr_shlvl2(t_env *env)
{
	long	intval;
	char	*newval;
	char	*incrval;

	if (env->val && ft_strisdigit(env->val))
	{
		if (env->val[0] == '-')
			incrval = ft_strdup("0");
		else
		{
			intval = ft_atol(env->val);
			if (intval >= 1000)
			{
				ft_desc_error("warning: shell level", env->val, 1,
					"too high, resetting to 1");
				incrval = ft_strdup("1");
			}
			else
				incrval = ft_itoa(intval + 1);
		}
	}
	else
		incrval = ft_strdup("1");
	newval = ft_strjoin_c(env->key, incrval, '=', 2);
	return (newval);
}

int	incr_shlvl(t_data *data)
{
	t_env	*env;
	t_env	*exp;
	char	*newval;

	env = data->envs->env;
	while (env)
	{
		if (!ft_ultimate_compare(env->key, "SHLVL"))
		{
			newval = incr_shlvl2(env);
			if (!newval)
				return (1);
		}
		env = env->next;
	}
	env = data->envs->env;
	exp = data->envs->exp;
	if (env_update(env, newval) || env_update(exp, newval))
		return (1);
	free(newval);
	return (0);
}

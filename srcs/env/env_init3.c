/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:13:16 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/03 19:01:38 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incs/minishell.h"

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
	env_update(env, newval);
	env_update(exp, newval);
	free(newval);
	return (0);
}

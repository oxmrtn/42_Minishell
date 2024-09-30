/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:04 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/30 17:28:17 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	envswap(t_data *data, t_env *n1, t_env *n2)
{
	t_env	*prev;
	t_env	*next;

	if (n1 == data->envs->exp)
		data->envs->exp = n2;
	prev = n1->prev;
	if (prev)
		prev->next = n2;
	next = n2->next;
	if (next)
		next->prev = n1;
	n1->next = next;
	n1->prev = n2;
	n2->prev = prev;
	n2->next = n1;
}

static void	sort_exp(t_data *data)
{
	t_env	*exp;
	int		sorted;

	sorted = 1;
	while (sorted)
	{
		exp = data->envs->exp;
		sorted = 0;
		while (exp && exp->next && exp->next)
		{
			if (ft_ultimate_compare(exp->key, exp->next->key) > 0)
			{
				envswap(data, exp, exp->next);
				sorted = 1;
			}
			else
				exp = exp->next;
		}
	}
}

static int	make_envexp2(t_data *data, char *entry)
{
	t_env	*env_entry;
	t_env	*exp_entry;

	env_entry = envnew_gtw(entry, 0);
	if (!env_entry)
		return (1);
	exp_entry = envnew_gtw(entry, 0);
	if (!exp_entry)
		return (free(env_entry), 1);
	ft_envadd_back(&data->envs->env, env_entry);
	ft_envadd_back(&data->envs->exp, exp_entry);
	return (0);
}

static int	make_envexp(t_data *data, char **env)
{
	t_env	*tmp_entry;
	size_t	i;

	i = 0;
	tmp_entry = NULL;
	while (env[i])
	{
		if (env[i][0] != '=')
		{
			if (!ft_strncmp(env[i], "_=", 2))
				tmp_entry = envnew_gtw(env[i], 0);
			else
				if (make_envexp2(data, env[i]))
					return (1);
		}
		i++;
	}
	if (tmp_entry)
	{
		ft_envadd_back(&data->envs->env, tmp_entry);
		data->envs->l_env = tmp_entry;
	}
	return (0);
}

int	env_init(t_data	*data, char **env)
{
	data->envs = malloc(sizeof(t_envs));
	if (!data->envs)
		return (1);
	data->envs->env = NULL;
	data->envs->exp = NULL;
	data->envs->tmpenv = NULL;
	data->envs->l_env = NULL;
	data->envs->envve = NULL;
	data->envs->tmpenvve = NULL;
	if (env[0])
		if (make_envexp(data, env))
			return (1);
	if (check_env(data))
		return (1);
	sort_exp(data);
	data->envs->envve = env_to_tab(data->envs->env);
	if (!data->envs->envve)
		return (1);
	return (0);
}

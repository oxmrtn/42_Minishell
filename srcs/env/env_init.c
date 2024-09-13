/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:04 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/13 14:36:55 by ebengtss         ###   ########.fr       */
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
	key = ft_strdup_till_i(str, i);
	if (c && c[1])
		val = ft_strdup(&c[1]);
	else
		val = NULL;
	return (ft_envnew(key, val, is_exp_no_val));
}

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
			if (strcmp(exp->key, exp->next->key) > 0)
			{
				envswap(data, exp, exp->next);
				sorted = 1;
			}
			else
				exp = exp->next;
		}
	}
}

static int	make_envexp(t_data *data, char **env)
{
	t_env	*env_entry;
	t_env	*exp_entry;
	size_t	i;

	i = 0;
	while (env[i])
	{
		env_entry = envnew_gtw(env[i], 0);
		exp_entry = envnew_gtw(env[i], 0);
		if (!env_entry || !exp_entry)
			return (1);
		ft_envadd_back(&data->envs->env, env_entry);
		if (!strncmp(env[i], "_=", 2))
		{
			free(exp_entry->key);
			free(exp_entry->val);
			free(exp_entry);
		}
		else
			ft_envadd_back(&data->envs->exp, exp_entry);
		i++;
	}
	data->envs->l_env = env_entry;
	return (0);
}

int	env_init(t_data	*data, char **env)
{
	data->envs = malloc(sizeof(t_envs));
	if (!data->envs)
		return (1);
	data->envs->env = NULL;
	data->envs->l_env = NULL;
	data->envs->exp = NULL;
	data->envs->tmpenv = NULL;
	data->envs->envve = NULL;
	if (!env[0])
		return (1);
	if (make_envexp(data, env))
		return (1);
	sort_exp(data);
	return (0);
}

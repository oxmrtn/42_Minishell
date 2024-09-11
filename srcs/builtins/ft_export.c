/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:35 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/11 17:19:20 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	exp_sortadd(t_data *data, t_env *exp, t_env *node)
{
	while (exp)
	{
		if (strcmp(exp->key, node->key) > 0)
		{
			if (exp == data->envs->exp)
			{
				ft_envadd_front(&data->envs->exp, node);
				data->envs->exp = node;
				return ;
			}
			if (exp->next)
			{
				node->next = exp->next;
				node->next->prev = node;
			}
			else
				node->next = NULL;
			exp->next = node;
			node->prev = exp;
			return ;
		}
		exp = exp->next;
	}
	ft_envadd_back(&data->envs->exp, node);
}

static int	expenv_add2(t_data *data, char *cmdve, int env_or_exp)
{
	t_env	*node;

	node = envnew_gtw(cmdve, env_or_exp);
	if (!node)
		return (1);
	if (env_or_exp)
		exp_sortadd(data, data->envs->exp, node);
	else
		ft_envadd_front(&data->envs->l_env, node);
	return (0);
}

static int	expenv_add(t_data *data, char *cmdve)
{
	char	*c;

	c = strchr(cmdve, '=');
	if (c == &cmdve[0] || ft_strisal(cmdve))
		return (ft_puterror("export: bad assignement\n"), 0);
	if (expenv_add2(data, cmdve, 1))
		return (1);
	if (c)
	{
		if (expenv_add2(data, cmdve, 0))
			return (1);
		if (data->envs->tenv)
			free(data->envs->tenv);
		data->envs->tenv = env_to_tab(data);
		if (!data->envs->tenv)
			return (1);
	}
	return (0);
}

static void	print_exp(t_env *env)
{
	while (env)
	{
		if (env->exp_noval)
			printf("%s\n", env->key);
		else
			printf("%s=\"%s\"\n", env->key, env->val);
		env = env->next;
	}
}

int	ft_export(t_data *data, char **cmdve)
{
	size_t	i;

	i = 1;
	if (!cmdve[1])
		print_exp(data->envs->exp);
	else
	{
		while (cmdve[i])
		{
			if (expenv_add(data, cmdve[i]))
				return (1);
			i++;
		}
	}
	print_exp(data->envs->exp);
	return (0);
}

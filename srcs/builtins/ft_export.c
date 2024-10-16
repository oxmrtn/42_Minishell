/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:35 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 17:55:41 by ebengtss         ###   ########.fr       */
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

int	expenv_add2(t_data *data, char *cmdve, int env_or_exp)
{
	t_env	*node;
	t_env	*env;

	if (env_or_exp)
		env = data->envs->exp;
	else
		env = data->envs->env;
	if (is_inenv_str(env, cmdve))
	{
		if (env_update(env, cmdve))
			return (1);
		return (0);
	}
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

	if (isvalid_env(cmdve, 0))
	{
		ft_desc_error("export", cmdve, 1, "not a valid identifier");
		return (1);
	}
	c = ft_strchr(cmdve, '=');
	if (c)
	{
		if (expenv_add2(data, cmdve, 2))
			return (2);
		if (expenv_add2(data, cmdve, 0))
			return (2);
		if (envtab_update(data))
			return (2);
	}
	else
		if (expenv_add2(data, cmdve, 1))
			return (2);
	return (0);
}

int	ft_export(t_data *data, char **cmdve)
{
	size_t	i;
	int		retval;

	i = 1;
	retval = 0;
	while (cmdve[i])
	{
		if (cmdve[i][0] && ft_strncmp(cmdve[i], "_=", 2) != 0
			&& ft_strncmp(cmdve[i], "_+=", 3) != 0)
		{
			if (retval != 1)
				retval = expenv_add(data, cmdve[i]);
			else
				expenv_add(data, cmdve[i]);
			if (retval == 2)
				return (-100);
		}
		i++;
	}
	if (data->envs->direrr && is_inenv_key(data->envs->env, "PWD"))
		data->envs->direrr = 0;
	if (i == 1)
		retval = print_exp(data->envs->exp);
	return (retval);
}

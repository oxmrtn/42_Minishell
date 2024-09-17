/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:35 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/17 17:18:30 by ebengtss         ###   ########.fr       */
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

int	env_update(t_env *lst, char *str)
{
	char	*c;
	size_t	i;

	i = 0;
	c = ft_strchr(str, '=');
	while (str[i] && &str[i] != c)
		i++;
	while (lst)
	{
		if (!strcmp(lst->key, str)) //replace strcmp for max len cmp
		{
			if (!c)
				return (1);
			if (lst->val)
				free(lst->val);
			lst->exp_noval = 0;
			if (c[1])
				lst->val = ft_strdup(&c[1]);
			else
				lst->val = NULL;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int	expenv_add2(t_data *data, char *cmdve, int env_or_exp)
{
	t_env	*node;

	if (env_or_exp)
		if (env_update(data->envs->exp, cmdve))
			return (0);
	if (!env_or_exp)
		if (env_update(data->envs->env, cmdve))
			return (0);
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

	c = ft_strchr(cmdve, '=');
	if (c == &cmdve[0] || ft_strisal(cmdve))
		return (ft_puterror("export: bad assignement\n"), 0);
	if (c)
	{
		if (expenv_add2(data, cmdve, 2))
			return (1);
		if (expenv_add2(data, cmdve, 0))
			return (1);
		if (data->envs->envve)
			free(data->envs->envve);
		data->envs->envve = env_to_tab(data);
		if (!data->envs->envve)
			return (1);
	}
	else
		if (expenv_add2(data, cmdve, 1))
			return (1);
	return (0);
}

int	ft_export(t_data *data, char **cmdve)
{
	size_t	i;

	i = 1;
	if (!cmdve[1])
		print_env(data->envs->exp, 1);
	else
	{
		while (cmdve[i])
		{
			if (expenv_add(data, cmdve[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

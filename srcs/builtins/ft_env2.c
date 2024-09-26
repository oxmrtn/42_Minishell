/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:27:05 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/26 18:36:39 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	env_update2(t_env *lst, char *c)
{
	lst->exp_noval = 0;
	if (c[1] && c[-1] && c[-1] == '+')
		lst->val = ft_strjoin_s1(lst->val, &c[1]);
	else
	{
		if (lst->val)
			free(lst->val);
		if (c[1])
			lst->val = ft_strdup(&c[1]);
		else
			lst->val = NULL;
	}
	if (c[1] && !lst->val)
		return (1);
	return (0);
}

int	env_update(t_env *lst, char *str)
{
	char	*c;
	size_t	i;

	i = 0;
	c = ft_strchr(str, '=');
	while (str[i] && str[i] != '+' && &str[i] != c)
		i++;
	if (!i)
		i = 1;
	while (lst)
	{
		if (!ft_strncmp(lst->key, str, i))
		{
			if (c)
				if (env_update2(lst, c))
					return (2);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	if (env_update(data->envs->env, cmdve))
		return (0);
	node = envnew_gtw(cmdve, 0);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->l_env, node);
	return (0);
}

void	tmp_env_clean(t_data *data)
{
	t_env	*l_node;

	l_node = data->envs->l_env;
	if (l_node->next)
	{
		ft_free_env(&l_node->next);
		data->envs->l_env->next = NULL;
	}
}

int	tmp_env_setup(t_data *data, t_cmds *cmd, int i)
{
	t_tokens	*tokens;
	int			check;

	tokens = skip_tokens(cmd, i);
	check = 0;
	while (tokens)
	{
		if (tokens->type == ENV
			&& ft_ultimate_compare(tokens->str, "env") != 0)
		{
			if (tmp_env_add(data, tokens->str))
				return (1);
			check = 1;
		}
		if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	if (!check)
		return (0);
	data->envs->tmpenv = data->envs->envve;
	data->envs->envve = env_to_tab(data);
	if (!data->envs->envve)
		return (1);
	return (0);
}

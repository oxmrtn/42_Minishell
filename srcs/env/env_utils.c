/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:32:48 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 15:49:14 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	env_update_keyval(t_env *lst, char *key, char *newval)
{
	while (lst)
	{
		if (!ft_ultimate_compare(key, lst->key))
		{
			if (lst->val)
				free(lst->val);
			if (newval)
				lst->val = ft_strdup(newval);
			else
				lst->val = NULL;
			if (!lst->val && newval)
				return (1);
			break ;
		}
		lst = lst->next;
	}
	return (0);
}

char	*env_getval_key(t_env *lst, char *key)
{
	char	*lookupval;

	lookupval = NULL;
	while (lst)
	{
		if (!ft_ultimate_compare(key, lst->key))
		{
			if (lst->val)
				lookupval = ft_strdup(lst->val);
			break ;
		}
		lst = lst->next;
	}
	return (lookupval);
}

int	envtab_update(t_data *data)
{
	if (data->envs->envve)
		ft_free_split(data->envs->envve);
	data->envs->envve = env_to_tab(data->envs->env);
	if (!data->envs->envve)
		return (1);
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
	while (str[i] && str[i] != '+' && &str[i] != c)
		i++;
	if (str[0] == '=' && !i)
		key = ft_strdup("=");
	else
		key = ft_strdup_till_i(str, i);
	if (c && c[1])
		val = ft_strdup(&c[1]);
	else
		val = NULL;
	return (ft_envnew(key, val, is_exp_no_val));
}

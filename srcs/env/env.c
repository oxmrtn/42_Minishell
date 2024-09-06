/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:04 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/06 18:14:56 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// static void	ft_envswap(t_data *data, t_env *n1, t_env *n2)
// {
// 	t_env	*post;
// 	t_env	*pre;

// 	pre = n1->prev;
// 	post = n2->next;
// 	if (n1 == data->envs->exp)
// 		data->envs->exp = n2;
// 	if (pre)
// 		pre->next = n2;
// 	if (post)
// 		post->prev = n1;
// 	n1->next = post;
// 	n1->prev = n2;
// 	n2->prev = pre;
// 	n2->next = n1;	
// }

// static void	sort_exp(t_data *data)
// {
// 	t_env	*exp;
// 	int		diff;
// 	int		check;

// 	exp = data->envs->exp;
// 	check = 1;
// 	while (check)
// 	{
// 		exp = data->envs->exp;
// 		while (exp->next)
// 		{
// 			diff = strcmp(exp->content, exp->next->content);
// 			if (diff > 0)
// 			{
// 				ft_envswap(data, exp, exp->next);
// 				check = 1;
// 			}
// 			else
// 				check = 0;
// 			exp = exp->next;
// 		}
// 	}
// 	data->envs->l_exp = ft_envlast(exp);
// }

static int	make_envexp(t_data *data, char **env)
{
	t_env	*env_entry;
	t_env	*exp_entry;
    size_t	i;

	i = 0;
    while (env[i + 1])
	{
		env_entry = ft_envnew(env[i]);
		exp_entry = ft_envnew(env[i]);
		if (!env_entry || !exp_entry)
			return (1);
		ft_envadd_back(&data->envs->env, env_entry);
		ft_envadd_back(&data->envs->exp, exp_entry);
		i++;
	}
	env_entry = ft_envnew(env[i]);
	if (!env_entry)
		return (1);
	ft_envadd_back(&data->envs->env, env_entry);
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
	data->envs->l_exp = NULL;
	if (!env[0])
		return (1);
	if (make_envexp(data, env))
		return (1);
	// sort_exp(data);
	return (0);
}

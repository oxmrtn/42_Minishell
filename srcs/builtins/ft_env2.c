/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:27:05 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/11 13:58:06 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	print_exp(t_env *env)
{
	int	retval;

	retval = 0;
	while (env)
	{
		if (env->exp_noval == 1)
			retval = printf("declare -x %s\n", env->key);
		else if (env->val)
			retval = printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else
			retval = printf("declare -x %s=\"\"\n", env->key);
		if (retval < 0)
		{
			ft_puterror("minishell: 'export': write error: ");
			perror(NULL);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

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
					return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	tmp_env_add(t_data *data, char *cmdve)
{
	t_env	*node;

	if (!data->envs->tmpenv)
		if (ft_envdup(data))
			return (1);
	if (is_inenv_str(data->envs->tmpenv, cmdve))
	{
		if (env_update(data->envs->tmpenv, cmdve))
			return (1);
		return (0);
	}
	node = envnew_gtw(cmdve, 0);
	if (!node)
		return (1);
	ft_envadd_back(&data->envs->tmpenv, node);
	return (0);
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
	data->envs->tmpenvve = data->envs->envve;
	data->envs->envve = env_to_tab(data->envs->tmpenv);
	if (!data->envs->envve)
		return (1);
	return (0);
}

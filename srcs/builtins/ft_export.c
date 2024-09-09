/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:35 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/09 17:35:04 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	exp_add(t_data *data, char *cmdve, char *c)
{
	t_env	*node;
	char	*buff;

	if (!c)
		buff = ft_strjoin(cmdve, "=''");
	else if (!c[1])
		buff = ft_strjoin(cmdve, "''");
	else
		buff = ft_strdup(cmdve);
	if (!buff)
		return (1);
	node = ft_envnew(buff);
	if (!node)
		return (free(buff), 1);
	free(buff);
	ft_envadd_back(&data->envs->l_exp, node);
	return (0);
}

static int	env_add(t_data *data, char *cmdve, char *c)
{
	t_env	*node;
	char	*buff;

	if (!c)
		return (0);
	buff = ft_strdup(cmdve);
	if (!buff)
		return (1);
	node = ft_envnew(buff);
	if (!node)
		return (free(buff), 1);
	free(buff);
	ft_envadd_front(&data->envs->l_env, node);
	return (0);
}

static int	expenv_add(t_data *data, char *cmdve)
{
	char	*c;

	c = strchr(cmdve, '=');
	if (c == &cmdve[0] || ft_strisal(cmdve))
	{
		ft_puterror("export: bad assignement\n");
		return (0);
	}
	if (exp_add(data, cmdve, c))
		return (1);
	if (env_add(data, cmdve, c))
		return (1);
	return (0);
}

int	ft_export(t_data *data, char **cmdve)
{
	size_t	i;

	if (!cmdve[1])
		print_env(data->envs->exp);
	else
	{
		i = 1;
		while (cmdve[i])
		{
			if (expenv_add(data, cmdve[i]))
				return (1);
			i++;
		}
	}
	print_env(data->envs->exp);
	return (0);
}

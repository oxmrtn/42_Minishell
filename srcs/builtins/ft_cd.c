/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:46:55 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/14 18:09:56 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
if getcwd fails, set pwd / old pwd as cmdve[1] 
(cd .. in a dir that doenst have parent dirs should set pwd to "..")
*/

static int	update_old_pwd(t_data *data)
{
	char	*temp;

	temp = getcwd(0, 0);
	if (!temp)
		return (1);
	temp = ft_strjoin_s2("OLDPWD=", temp);
	if (!temp)
		return (1);
	if (env_update(data->envs->env, temp)
		|| env_update(data->envs->exp, temp))
		return (free(temp), 1);
	free(temp);
	return (0);
}

static char	*get_home(t_data *data)
{
	t_env	*node;

	node = data->envs->env;
	while (node)
	{
		if (!ft_ultimate_compare("HOME", node->key))
			return (ft_strdup(node->val));
		node = node->next;
	}
	return (NULL);
}

static int	handle_flag(t_data *data)
{
	char	*oldpwd;

	oldpwd = env_getval_key(data->envs->env, "OLDPWD");
	if (!oldpwd)
		return (ft_puterror("minishell: 'cd': OLDPWD not set\n"), 1);
	if (update_old_pwd(data))
		return (free(oldpwd), -100);
	if (chdir(oldpwd) != 0)
		return (free(oldpwd), 1);
	free(oldpwd);
	return (ft_pwd(data));
}

static int	ft_cd2(t_data *data, char **cmdve)
{
	char	*actual_path;
	char	*temp;

	if (!cmdve[1])
	{
		temp = get_home(data);
		if (!temp)
			return (ft_puterror("minishell: 'cd': HOME not set\n"), 1);
		if (chdir(temp) != 0)
			return (perror("minishell: 'cd':"), free(temp), 1);
		free(temp);
	}
	else
		if (chdir(cmdve[1]) != 0)
			return (perror("minishell: 'cd':"), 1);
	actual_path = getcwd(0, 0);
	if (actual_path)
		return (0);
	if (env_update_keyval(data->envs->env, "PWD", actual_path)
		|| env_update_keyval(data->envs->exp, "PWD", actual_path))
		return (free(actual_path), -100);
	free(actual_path);
	return (0);
}

int	ft_cd(t_data *data, char **cmdve)
{
	if (cmdve[1] && cmdve[2])
		return (ft_puterror("minishell: 'cd': too many arguments\n"), 1);
	if (data->envs->direrr)
	{
		if (expenv_add2(data, "OLDPWD=", 0))
			return (1);
		data->envs->direrr = 0;
	}
	if (cmdve[1] && !ft_ultimate_compare(cmdve[1], "-"))
		return (handle_flag(data));
	if (update_old_pwd(data))
		return (-100);
	return (ft_cd2(data, cmdve));
}

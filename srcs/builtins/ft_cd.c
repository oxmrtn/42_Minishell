/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:46:55 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 19:41:59 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_cd5(void)
{
	char	*tmp;

	tmp = getcwd(0, 0);
	if (!tmp)
		return (0);
	free(tmp);
	return (1);
}

static char	*ft_cd4(t_data *data, char *cmdve)
{
	char	*newpwd;

	newpwd = getcwd(0, 0);
	if (!newpwd && !cmdve)
		newpwd = env_getval_key(data->envs->env, "HOME");
	else if (!newpwd && cmdve)
		newpwd = ft_strdup(cmdve);
	if (!newpwd)
		return (NULL);
	return (newpwd);
}

static int	ft_cd3(t_data *data, char *cmdve, char *oldpwd, int retval)
{
	char		*newpwd;
	const int	ispwd = is_inenv_key(data->envs->env, "PWD");

	if (oldpwd && update_old_pwd(data, oldpwd))
		return (-100);
	newpwd = ft_cd4(data, cmdve);
	if (!newpwd)
		return (-100);
	if (!data->tmppwd)
		data->tmppwd = ft_strdup(newpwd);
	else if (ft_cd5())
	{
		free(data->tmppwd);
		data->tmppwd = ft_strdup(newpwd);
	}
	else
		data->tmppwd = ft_strjoin_c(data->tmppwd, newpwd, '/', 1);
	if (!data->tmppwd)
		return (-100);
	if (ispwd)
		if (env_update_keyval(data->envs->env, "PWD", data->tmppwd)
			|| env_update_keyval(data->envs->exp, "PWD", data->tmppwd))
			return (free(newpwd), -100);
	free(newpwd);
	return (retval);
}

static int	ft_cd2(t_data *data, char **cmdve)
{
	char	*temp;

	if (!cmdve[1])
	{
		temp = env_getval_key(data->envs->env, "HOME");
		if (!temp)
			return (ft_puterror("minishell: 'cd': HOME not set\n"), 1);
		if (chdir(temp) != 0)
			return (ft_desc_error("cd", temp, 1, NULL), free(temp), 1);
		free(temp);
	}
	else
		if (chdir(cmdve[1]) != 0)
			return (ft_desc_error("cd", cmdve[1], 1, NULL), 1);
	if (data->envs->direrr)
	{
		data->envs->direrr = 0;
		if (is_inenv_key(data->envs->env, "OLDPWD"))
			return (env_update_keyval(data->envs->env, "OLDPWD", NULL));
		if (expenv_add2(data, "OLDPWD=", 0))
			return (1);
	}
	return (0);
}

int	ft_cd(t_data *data, char **cmdve)
{
	char	*oldpwd;
	int		retval;

	oldpwd = NULL;
	if (cmdve[1] && cmdve[2])
		return (ft_puterror("minishell: 'cd': too many arguments\n"), 1);
	oldpwd = env_getval_key(data->envs->env, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(0, 0);
	if (!ft_cd5())
		ft_desc_error("cd", "error retrieving current directory", 0, NULL);
	if (!oldpwd && data->tmppwd)
		oldpwd = ft_strdup(data->tmppwd);
	if (cmdve[1] && !ft_ultimate_compare(cmdve[1], "-"))
		retval = cd_handle_flag(data);
	else
		retval = ft_cd2(data, cmdve);
	if (retval != 0)
		if (oldpwd)
			free(oldpwd);
	if (retval != 0)
		return (retval);
	return (ft_cd3(data, cmdve[1], oldpwd, retval));
}

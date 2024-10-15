/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:43:14 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/15 16:44:23 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	update_old_pwd(t_data *data, char *oldpwd)
{
	char	*temp;

	temp = ft_strjoin_s2("OLDPWD=", oldpwd);
	if (!temp)
	{
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	if (env_update(data->envs->env, temp)
		|| env_update(data->envs->exp, temp))
		return (free(temp), 1);
	free(temp);
	return (0);
}

int	cd_handle_flag(t_data *data)
{
	char	*oldpwd;

	oldpwd = env_getval_key(data->envs->env, "OLDPWD");
	if (!oldpwd)
		return (ft_puterror("minishell: 'cd': OLDPWD not set\n"), 1);
	if (chdir(oldpwd) != 0)
		return (free(oldpwd), 1);
	free(oldpwd);
	return (ft_pwd(data));
}

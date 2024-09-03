/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:56:04 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/03 14:04:39 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	make_env(t_data	*data, char **env)
{
	t_env	*env_entry;
    size_t	i;

    i = 0;
    while (env[i])
	{
		env_entry = ft_envnew(env[i]);
		if (!env_entry)
			return (1);
		ft_envadd_back(&data->env, env_entry);
		i++;
	}
    return (0);
}

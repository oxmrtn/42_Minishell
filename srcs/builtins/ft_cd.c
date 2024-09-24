/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:46:55 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/24 14:44:26 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*get_root(t_data *data)
{
	t_env	*node;

	node = data->envs->env;
	while (node)
	{
		if (!ft_ultimate_compare("HOME", node->key)
			|| !ft_ultimate_compare("ZDOTDIR", node->key))
		{
			return(ft_strdup(node->val));
		}
		node = node->next;
	}
	return (NULL);
}

static void	ft_env_update(t_data *data, char *new_val)
{
	t_env	*node;

	node = data->envs->env;
	while (node)
	{
		if (!ft_ultimate_compare("PWD", node->key))
		{
			free(node->val);
			node->val = ft_strdup(new_val);
			return (free(new_val));
		}
		node = node->next;
	}
	free(new_val);
}

int	ft_cd(t_data *data, char **cmdve)
{
	char	*actual_path;
	char	*temp;
	
	if (cmdve[1] && cmdve[2])
		return (ft_puterror("minishell error: cd too many arguments\n"), 1);
	if (!cmdve[1])
	{
		temp = get_root(data);
		if (!temp)
			return (ft_puterror("minishell error: cd error\n"), -100);
		if (chdir(temp) != 0)
			return(perror("cd"), free(temp), 1);
		free(temp);
	}
	else
		if (chdir(cmdve[1]) != 0)
			return(perror("cd"), 1);
	actual_path = getcwd(0, 0);
	if (!actual_path)
		return (0);
	ft_env_update(data, actual_path);
	return (0);	
}

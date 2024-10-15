/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:18 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/11 14:04:17 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*get_value_env(char *key, t_data *data)
{
	t_env	*node;

	node = data->envs->env;
	while (node)
	{
		if (!ft_strncmp(key, node->key, ft_strlen(key)))
		{
			return (ft_strdup(node->val));
		}
		node = node->next;
	}
	return (NULL);
}

int	ft_pwd(t_data *data)
{
	char	*test;
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		pwd = get_value_env("PWD", data);
		if (!pwd)
			return (ft_puterror("minishell error : pwd has failled\n"), -100);
	}
	test = ft_strjoin(pwd, "\n");
	free(pwd);
	if (test)
	{
		if (write(STDOUT_FILENO, test, ft_strlen(test)) < 0)
		{
			ft_puterror("minishell: 'pwd': write error: ");
			perror(NULL);
			return (free(test), 1);
		}
	}
	free(test);
	return (0);
}

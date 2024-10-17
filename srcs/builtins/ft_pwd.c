/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:18 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 18:28:55 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_desc_error("pwd", "error retrieving current directory", 0, NULL);
		return (1);
	}
	if (write(STDOUT_FILENO, pwd, ft_strlen(pwd)) < 0)
	{
		free(pwd);
		ft_puterror("minishell: 'pwd': write error: ");
		perror(NULL);
		return (1);
	}
	free(pwd);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

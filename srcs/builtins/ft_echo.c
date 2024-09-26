/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:45:11 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/26 16:38:29 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	echo_option_check(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!i && arg[i] != '-')
			return (1);
		if (i > 0 && arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **cmdve)
{
	int		i;
	int		flag;
	char	*buffer;

	i = 1;
	flag = 0;
	buffer = NULL;
	if (cmdve[i] && cmdve[i][1] && !echo_option_check(cmdve[i]))
	{
		flag = 1;
		i++;
	}
	if (!cmdve[i])
		return (0);
	while (cmdve[i])
		buffer = ft_strjoin_c(buffer, cmdve[i++], ' ', 1);
	if (!flag)
		buffer = ft_strjoin_s1(buffer, "\n");
	if (!buffer)
		return (-100);
	if (write(STDOUT_FILENO, buffer, ft_strlen(buffer)) < 0)
	{
		ft_puterror("minishell error : cannot write in outfile\n");
		return (free(buffer), 1);
	}
	fflush(stdout);
	return (free(buffer), 0);
}

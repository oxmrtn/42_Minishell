/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:45:11 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/25 14:42:38 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_echo(char **cmdve)
{
	int		i;
	int		flag;
	char	*buffer;

	i = 1;
	flag = 0;
	buffer = NULL;
	if (cmdve[i] && !ft_ultimate_compare(cmdve[i], "-n"))
	{
		flag = 1;
		i++;
	}
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

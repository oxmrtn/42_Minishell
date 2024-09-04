/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:25:31 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/03 16:37:22 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	reset_fds(void)
{
	if (dup2(STDIN_FILENO, STDIN_FILENO) == -1)
		return (perror(NULL), 1);
	if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
		return (perror(NULL), 1);
	return (0);
}

void	cleanup_exec(char ***cmdve)
{
	int i;

	i = 0;
	if (*cmdve)
	{
		if (**cmdve)
		{
			while (cmdve[i])
			{
				ft_free_split(cmdve[i]);
				i++;
			}
		}
		free(cmdve);
	}
}

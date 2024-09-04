/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:06:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 17:15:43 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	delete_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len -1] = '\0';
}

int	ft_get_history()
{
	int		fd;
	char	*line;

	fd = open(".history.txt", O_RDONLY | O_CREAT);
	if (fd <= 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	while(line)
	{
		delete_end(line);
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	ft_write_history(t_cmds *cmds)
{
	int	fd;

	fd = open(".history.txt", O_WRONLY | O_CREAT | O_APPEND);
	if (fd <= 0)
		return (1);
	while (cmds)
	{
		write(fd, cmds->cmd, ft_strlen(cmds->cmd));
		write(fd, "\n", 1);
		cmds = cmds->next;
	}
	close(fd);
	return (0);
}
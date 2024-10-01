/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:22:35 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 11:21:38 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_launch_heredocs(char *limiter, t_data *data)
{
	int				fd;
	char			*buffer;

	fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY);
	if (fd <= 0)
		return (1);
	buffer = get_next_line(1);
	if (!buffer)
		return (close(fd), 0);
	buffer = ft_flat_string(buffer, data);
	while (buffer && ft_ultimate_compare(limiter, buffer))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(1);
		if (!buffer)
			return (close(fd), 0);
		buffer = ft_flat_string(buffer, data);
	}
	close(fd);
	return (0);
}

int	ft_heredoc_handler(t_tokens *head, t_data *data)
{
	while (head && head->type != CMD)
	{
		if (head->type == LIMITER)
			if (ft_launch_heredocs(head->str, data))
				return (1);
		head = head->next;
	}
	return (0);
}

int	ft_ask_handler(t_tokens *head, t_data *data)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	while (head)
	{
		if (head->type == ASK)
		{
			temp = get_next_line(1);
			if (!temp)
				return (1);
			temp2 = ft_strdup_till_i(temp, (int)ft_strlen(temp) - 1);
			if (!temp2)
				return (1);
			free(temp);
			head->next = create_token_list(temp2, data);
			if (!head->next)
				return (1);
			free(temp2);
			head->type = PIPE;
			return (0);
		}
		head = head->next;
	}
	return (0);
}

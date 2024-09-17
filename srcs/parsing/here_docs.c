/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:22:35 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 17:15:25 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_launch_heredocs(char *limiter, t_data *data)
{
	int				fd;
	char			*buffer;
	int				max;

	fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY);
	if (fd <= 0)
		return ;
	buffer = get_next_line(1);
	buffer = ft_flat_string(buffer, data);
	max = ft_max(ft_strlen(buffer) - 1, ft_strlen(limiter));
	while (buffer && ft_strncmp(limiter, buffer, max))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(1);
		buffer = ft_flat_string(buffer, data);
		max = ft_max(ft_strlen(buffer) - 1, ft_strlen(limiter));
	}
	close(fd);
}

void	ft_heredoc_handler(t_tokens *head, t_data *data)
{
	while (head && head->type != CMD)
	{
		if (head->type == LIMITER)
			ft_launch_heredocs(head->str, data);
		head = head->next;
	}
}

void	ft_ask_handler(t_tokens *head, t_data *data)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	while (head)
	{
		if (head->type == ASK)
		{
			temp = get_next_line(1);
			temp2 = ft_strdup_till_i(temp, (int)ft_strlen(temp) - 1);
			free(temp);
			head->next = create_token_list(temp2, data);
			free(temp2);
			head->type = PIPE;
			ft_heredoc_handler(head, data);
		}
		head = head->next;
	}
}

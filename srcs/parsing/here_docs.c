/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:22:35 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/10 12:27:24 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_launch_heredocs(char *limiter)
{
	const size_t	len = ft_strlen(limiter);
	int				fd;
	char			*buffer;

	fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY);
	if (fd <= 0)
		return ;
	buffer = get_next_line(1);
	while (buffer && ft_strncmp(buffer, limiter, len))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(1);
	}
	close(fd);
}

void	ft_heredoc_handler(t_tokens *head)
{
	while (head && head->type != CMD)
	{
		if (head->type == LIMITER)
			ft_launch_heredocs(head->str);
		head = head->next;
	}
}

static void	handle_ask(t_tokens *head)
{
	char	*temp;

	temp = get_next_line(1);
	add_new_token(temp, head, CMD);
	free(temp);
}

void	ft_ask_handler(t_tokens *head, t_data *data)
{
	char	*temp;
	char	**splitted;
	int		i;

	i = 0;
	temp = NULL;
	while (head)
	{
		if (head->type == ASK)
		{
			temp = get_next_line(1);
			create_token_list(temp, data);
			free(temp);
			head->type = PIPE;
			ft_heredoc_handler(head);
		}
		head = head->next;
	}
}

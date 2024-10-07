/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:22:35 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/07 18:01:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*ft_launch_heredocs2(int *fd, t_data *data)
{
	char	*temp;

	*fd = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd <= 0)
		return (NULL);
	if (unlink(".heredoc") == -1)
		return (NULL);
	if (add_heredoc_list(*fd, data))
		return (NULL);
	write(1, "> ", 2);
	temp = get_next_line(STDIN_FILENO);
	if (!temp)
		return (NULL);
	temp[ft_strlen(temp) - 1] = '\0';
	return (temp);
}

static int	ft_launch_heredocs(char *limiter, t_data *data)
{
	int		fd;
	char	*buffer;
	char	*temp;

	temp = ft_launch_heredocs2(&fd, data);
	if (!temp)
		return (1);
	while (temp && ft_ultimate_compare(temp, limiter))
	{
		write(1, "> ", 2);
		buffer = ft_flat_string(temp, data);
		if (!buffer)
			return (free(temp), 1);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(temp);
		free(buffer);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
			return (0);
		temp[ft_strlen(temp) - 1] = '\0';
	}
	return (free(temp), 0);
}

int	ft_heredoc_handler(t_tokens *head, t_data *data)
{
	int		flag;

	flag = 0;
	while (head)
	{
		while (head && head->type != PIPE)
		{
			if (head->type == LIMITER)
			{			
				if (flag == 1)
					del_top_hd(data);
				else if (flag == 0)
					flag = 1;
				if (ft_launch_heredocs(head->str, data))
					return (1);
			}
			head = head->next;
		}
		if (!head)
			return (0);
		head = head->next;
	}
	return (0);
}

int	ft_ask_handler(t_tokens *head, t_data *data)
{
	char	*temp;
	char	*temp2;

	while (head)
	{
		if (head->type == ASK)
		{
			write(1, "> ", 2);
			temp = get_next_line(1);
			if (!temp)
				return (1);
			temp2 = ft_strdup_till_i(temp, (int)ft_strlen(temp) - 1);
			if (!temp2)
				return (1);
			free(temp);
			head->next = create_token_list(temp2, data);
			free(temp2);
			if (!head->next)
				return (1);
			head->type = PIPE;
			return (0);
		}
		head = head->next;
	}
	return (0);
}

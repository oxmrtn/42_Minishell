/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 14:03:51 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_syntax_error(t_tokens *head, t_data *data)
{
	while (head)
	{
		if (head->type == ERROR)
		{
			ft_desc_error(head->str, "syntax error", 0, NULL);
			data->exit_status = 2;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	ft_parser(char *line, t_cmds **commands, t_data *data)
{
	t_cmds	*new_node;

	if (!ft_ultimate_compare(line, ":") || !ft_ultimate_compare(line, "!"))
		return (data->exit_status = 0, 2);
	new_node = malloc(sizeof(t_cmds));
	if (!new_node)
		return (1);
	new_node->tokens = create_token_list(line, data);
	if (!new_node->tokens)
		return (free(new_node), 1);
	if (new_node->tokens == (void *)-1)
		return (free(new_node), 2);
	if (ft_syntax_error(new_node->tokens, data))
		return (ft_free_invalid_syntax(new_node), 2);
	if (ft_heredoc_handler(new_node->tokens, data))
		return (ft_free_invalid_syntax(new_node), 2);
	if (add_commands(new_node, commands))
		return (1);
	return (0);
}

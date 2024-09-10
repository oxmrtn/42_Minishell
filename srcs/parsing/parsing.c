/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/10 12:24:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_syntax_error(t_tokens *head)
{
	while (head)
	{
		if (head->type == ERROR)
		{
			ft_puterror("minishell error: syntax error\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	ft_parser(char *line, t_cmds **commands, t_data *data)
{
	t_cmds	*new_node;

	if (ft_is_variable_declaration(line) == 0)
	{
		if (!ft_add_variable(line, data))
			return (1);
	}
	else
	{
		new_node = malloc(sizeof(t_cmds));
		if (!new_node)
			return (1);
		new_node->cmd = ft_strdup(line);
		if (!new_node->cmd)
			return (free(new_node), 1);
		new_node->tokens = create_token_list(line, data);
		if (!new_node->tokens)
			return (1);
		ft_heredoc_handler(new_node->tokens);
		ft_ask_handler(new_node->tokens, data);
		if (ft_syntax_error(new_node->tokens))
			return (ft_free_invalid_syntax(new_node), 1);
		if (add_commands(new_node, commands) == 1)
			return (1);
	}
	return (0);
}

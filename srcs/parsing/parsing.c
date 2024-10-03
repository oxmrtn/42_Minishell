/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:03:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/03 18:09:05 by mtrullar         ###   ########.fr       */
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

	if (!ft_ultimate_compare(line, ":") || !ft_ultimate_compare(line, "!"))
		return (printf("1"), 1);
	new_node = malloc(sizeof(t_cmds));
	if (!new_node)
		return (printf("2"), 1);
	new_node->tokens = create_token_list(line, data);
	if (!new_node->tokens)
		return (free(new_node), printf("3"), 1);
	if (ft_syntax_error(new_node->tokens))
		return (ft_free_invalid_syntax(new_node), printf("4"), 1);
	if (ft_heredoc_handler(new_node->tokens, data))
		return (ft_free_invalid_syntax(new_node), printf("5"), 1);
	if (ft_ask_handler(new_node->tokens, data))
		return (ft_free_invalid_syntax(new_node), printf("6"), 1);
	if (add_commands(new_node, commands))
		return (printf("7"), 1);
	return (0);
}

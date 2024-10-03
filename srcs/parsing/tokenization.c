/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:20:36 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/03 17:42:08 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	handle_env(t_tokens *node)
{
	t_tokens	*tmp;

	tmp = node->next;
	node->type = CMD;
	if (!tmp)
		return (1);
	while (tmp && (!(tmp->str[0] == '|'
				|| tmp->str[0] == '>' || tmp->str[0] == '<')))
	{
		if (!ft_strchr(tmp->str, '='))
		{
			tmp = tmp->prev;
			while (tmp != node)
			{
				tmp->type = ENV;
				tmp = tmp->prev;
			}
			node->type = ENV;
			break ;
		}
		tmp->type = ARGS;
		tmp = tmp->next;
	}
	return (1);
}

int	ft_is_commands(t_tokens *node)
{
	if (!ft_ultimate_compare(node->str, "env"))
		return (handle_env(node));
	if (node->str)
		if (!ft_strncmp(node->str, "|", 1) || !ft_strncmp(node->str, ">", 1)
			|| !ft_strncmp(node->str, "<", 1))
			return (0);
	if (!node->prev)
		return (1);
	else if (!ft_strncmp(node->prev->str, "|", 1))
		return (1);
	else if (node->prev->type == INFILE && count_cmd(node) == 0)
		return (1);
	else if (node->prev->type == LIMITER && count_cmd(node) == 0)
		return (1);
	else if (node->prev->type == OUTFILE && count_cmd(node) == 0)
		return (1);
	else if (node->prev->type == ENV)
		return (1);
	return (0);
}

static void	ft_check_pipe(t_tokens *node)
{
	if (node->str[ft_strlen(node->str) - 1] == '|')
	{
		node->str[ft_strlen(node->str) - 1] = '\0';
		add_tokens_between("|", node, PIPE);
	}
}

int	ft_is_args(t_tokens *node)
{
	if (ft_strchr(node->str, '&') || ft_strchr(node->str, ';')
		|| ft_strchr(node->str, '(') || ft_strchr(node->str, ')'))
		node->type = ERROR;
	else if (node->prev == NULL)
		return (0);
	else if (count_cmd(node) > 0 && (node->prev->type == OUTFILE
			|| node->prev->type == INFILE))
		return (ft_check_pipe(node), 1);
	if (node->prev->type == ARGS || node->prev->type == CMD)
		return (ft_check_pipe(node), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:20:36 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/18 14:21:40 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int handle_env(t_tokens *node)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = node->next;
	if (!tmp)
		return (1);
	while (tmp && ft_strchr(tmp->str, '='))
	{
		tmp->type = ENV;
		tmp = tmp->next;
		i++;
	}
	if (i > 0)
		node->type = ENV;
	return (1);
}

int	ft_is_commands(t_tokens *node)
{
	if (!ft_ultimate_compare(node->str, "env"))
		return (handle_env(node));
	else if (!ft_isalnum(node->str[0]))
		return (0);
	else if (!node->prev)
		return (1);
	else if (!ft_strncmp(node->prev->str, "|", 1))
		return (1);
	else if (node->prev->type == INFILE)
		return (1);
	else if (node->prev->type == LIMITER)
		return (1);
	else if (node->prev->type == ENV)
		return (1);
	else
		return (0);
}

int	ft_is_args(t_tokens *node)
{
	if (node->prev == NULL)
		return (0);
	return (node->prev->type == ARGS || node->prev->type == CMD);
}

static void	ft_set_redirect(t_tokens *current, t_type to_set )
{
	if ((current->prev && current->next)
		&& ((current->prev->type == REDIR || current->next->type == REDIR)
			|| (current->prev->type == PIPE || current->next->type == PIPE)))
		current->type = ERROR;
	else
	{
		if (current->next)
		{
			current->type = REDIR;
			current->next->type = to_set;
		}
		else
			current->type = ERROR;
	}
}

int	ft_is_redirect_sign(t_tokens *current)
{
	if (!ft_strncmp(current->str, ">>", 2))
		return (ft_set_redirect(current, APPEND), 1);
	else if (!ft_strncmp(current->str, ">", 1))
		return (ft_set_redirect(current, OUTFILE), 1);
	else if (!ft_strncmp(current->str, "<<", 2))
		return (ft_set_redirect(current, LIMITER), 1);
	else if (!ft_strncmp(current->str, "<", 1))
		return (ft_set_redirect(current, INFILE), 1);
	return (0);
}

int	ft_is_pipe(t_tokens *current)
{
	if (ft_strncmp(current->str, "|", 1) == 0)
	{
		if (!current->next)
		{
			current->type = ASK;
			return (2);
		}
		else if (current->prev && current->prev->type == REDIR)
		{
			current->type = ERROR;
			return (0);
		}
		else
			return (1);
	}
	else
		return (0);
}

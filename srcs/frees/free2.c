/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:38:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:36 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_tokens(t_tokens *tok)
{
	t_tokens	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->str);
		free(tmp);
	}
}

void	ft_free_commands(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		ft_free_tokens(tmp->tokens);
		free(tmp->cmd);
		free(tmp);
	}
}

void	ft_free_invalid_syntax(t_cmds *to_free)
{
	ft_free_tokens(to_free->tokens);
	free(to_free);
}

void	ft_free_var(t_var *node)
{
	t_var	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->name);
		free(temp->content);
		free(temp);
	}
}

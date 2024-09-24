/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionnal_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:38:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/24 13:51:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_invalid_syntax(t_cmds *to_free)
{
	free(to_free->cmd);
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

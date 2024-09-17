/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditionnal_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:38:10 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 17:17:38 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free_invalid_syntax(t_cmds *to_free)
{
	free(to_free->cmd);
	ft_free_tokens(to_free->tokens);
	free(to_free);
}

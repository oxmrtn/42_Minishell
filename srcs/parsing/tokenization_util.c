/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:40:43 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 16:57:56 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	ft_set_redirect(t_tokens *current, t_type to_set )
{
	if ((current->prev && current->next)
		&& ((current->prev->type == REDIR || current->next->type == REDIR)))
		current->type = ERROR;
	{
		if (current->next)
		{
			current->type = REDIR;
			if (ft_strncmp(current->next->str, "|", 1)
				&& ft_strncmp(current->next->str, "<", 1)
				&& ft_strncmp(current->next->str, ">", 1))
				current->next->type = to_set;
			else
			{
				current->type = ERROR;
				current->next->type = ERROR;
			}
		}
		else
			current->type = ERROR;
	}
}

int	ft_is_redirect_sign(t_tokens *current)
{
	if (!ft_ultimate_compare(current->str, ">>"))
		return (ft_set_redirect(current, APPEND), 1);
	else if (!ft_ultimate_compare(current->str, ">"))
		return (ft_set_redirect(current, OUTFILE), 1);
	else if (!ft_ultimate_compare(current->str, "<<"))
		return (ft_set_redirect(current, LIMITER), 1);
	else if (!ft_ultimate_compare(current->str, "<"))
		return (ft_set_redirect(current, INFILE), 1);
	else if (!ft_ultimate_compare(current->str, ">")
		|| !ft_ultimate_compare(current->str, "<"))
		return (current->type = ERROR, 1);
	return (0);
}

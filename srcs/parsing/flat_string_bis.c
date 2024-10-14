/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_string_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:59:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/15 00:51:17 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	flat_string_cond_1(int res, int *i)
{
	if (res < 0)
		return (1);
	*i += res;
	return (0);
}

int	flat_string_cond_2(char **buf, char *str, int i, t_nk check)
{
	*buf = ft_append(*buf, str, i, check.i);
	if (*buf == NULL)
		return (1);
	return (0);
}

int	flat_string_init(t_nk *check, char **buf)
{
	check->i = ((check->j = ((check->k = 0))));
	*buf = ft_strdup("");
	if (*buf == NULL)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_string_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:59:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 17:01:02 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	cond_lim(t_tokens *current, char *str, t_nk *c, char **buf)
{
	if (!current || (current && current->type != LIMITER))
		return (0);
	if (((current && current->type == LIMITER)
			|| (!(c->k == 1 && c->i == 0))) && str[c->m] == '$')
	{
		if (str[c->m + 1] && str[c->m + 1] == 34 && (c->m == 0
				|| (c->m > 1 && str[c->m - 1] != '$')))
			c->m = c->m + 1 - 1;
		else
		{
			*buf = ft_strjoin_s1(*buf, "$");
			if (!(*buf))
				return (1);
		}
		return (1);
	}
	return (0);
}

int	fsc1(int res, int *i)
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
	check->m = -1;
	check->i = ((check->j = ((check->k = 0))));
	*buf = ft_strdup("");
	if (*buf == NULL)
		return (1);
	return (0);
}

int	big_cond(char *s2, int i)
{
	return (s2[i] && ((!(s2[i] >= 0 && s2[i] <= 47)
				|| (ft_iqt(s2[i]) && i == 0))
			&& !(s2[i] >= 58 && s2[i] <= 62)
			&& !(s2[i] >= 91 && s2[i] <= 94) && s2[i] != 96 && s2[i] != 64
			&& s2[i] != '\n' && !(s2[i] >= 123 && s2[i] <= 127))
		&& (!(i == 1 && s2[i - 1] == '?'))
		&& (!(i == 1 && ft_isdigit(s2[i - 1])))
		&& (!(i == 1 && ft_iqt(s2[i - 1]))));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:02:18 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 14:08:36 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_mixed_bis(char c, int *i, int *latest)
{
	if (c == 39)
	{
		if ((*i) == 0)
			*i = 1;
		else if ((*i) == 1)
		{
			if (c == 39)
			{
				if (*latest == 1)
					return (1);
			}
			else if (c == 34)
				if (*latest == 2)
					return (1);
			*i = 0;
		}
		if (c == 39)
			*latest = 2;
		else
			*latest = 1;
	}
	return (0);
}

static int	ft_check_mixed_quote(char *str)
{
	int		i;
	t_nk	states;
	int		latest;

	i = 0;
	states.i = 0;
	states.j = 0;
	latest = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (ft_mixed_bis(str[i], &states.j, &latest))
				return (1);
		}
		else if (str[i] == 34)
			if (ft_mixed_bis(str[i], &states.i, &latest))
				return (1);
		i++;
	}
	return (0);
}

int	ft_check_quote_syntax(char *str)
{
	int		i;
	t_nk	count;
	char	c;

	i = 0;
	count.i = 0;
	if (ft_check_mixed_quote(str))
		return (ft_puterror("minishell error: mixed quote\n"), 1);
	while (str && str[i])
	{
		c = str[i++];
		if (c && (c == 39 || c == 34))
		{
			count.i = 1;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == '\0')
				return (ft_puterror("minishell error: unclosed quote\n"), 1);
			if (c == str[i++])
				count.i = 0;
		}
	}
	if (count.i != 0)
		return (ft_puterror("minishell error: unclosed quote\n"), 1);
	return (0);
}

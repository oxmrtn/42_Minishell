/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:09:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/16 16:49:37 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!i && (str[i] != '-' && !ft_isdigit(str[i])))
			|| (i > 0 && !ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_iqt(int c)
{
	return ((c == 34 || c == 39));
}
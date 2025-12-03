/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:09:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:35 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_iswhite(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (1);
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			return (0);
		i++;
	}
	return (1);
}

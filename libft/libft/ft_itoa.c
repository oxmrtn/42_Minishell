/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:28:54 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static char	*ft_itoa_bis(int n, char *res, int i, int neg)
{
	int	tmp;

	tmp = n;
	if (neg)
	{
		res[0] = '-';
		res[i + 1] = '\0';
	}
	else
	{
		res[i] = '\0';
		i--;
	}
	while (i >= 0 + neg)
	{
		res[i] = (tmp % 10) + '0';
		tmp /= 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		neg;
	int		tmp;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	tmp = n;
	i = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	result = malloc(sizeof(char) * (i + neg + 1));
	if (!result)
		return (NULL);
	ft_itoa_bis(n, result, i, neg);
	return (result);
}

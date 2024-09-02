/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:22 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:50:13 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void	ft_putnbr_base(int nbr, char *base, int *total)
{
	unsigned int	long_nbr;
	unsigned int	len_base;

	long_nbr = nbr;
	len_base = 16;
	if (1)
	{
		if (long_nbr < len_base)
			*total += ft_putchar_int(base[long_nbr], 1);
		else
		{
			ft_putnbr_base(long_nbr / len_base, base, total);
			ft_putnbr_base(long_nbr % len_base, base, total);
		}
	}
}

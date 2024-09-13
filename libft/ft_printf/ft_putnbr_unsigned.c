/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:09:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:50:08 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void	ft_putnbr_unsigned(unsigned int nbr, int fd, int *tot)
{
	unsigned int	tmp;

	if (nbr <= 9 && nbr >= 0)
		*tot += ft_putchar_int((nbr + '0'), fd);
	else if (nbr < 0)
	{
		*tot += ft_putchar_int('-', fd);
		ft_putnbr_unsigned((nbr * -1), fd, tot);
	}
	else
	{
		tmp = nbr % 10;
		ft_putnbr_unsigned(nbr / 10, fd, tot);
		*tot += ft_putchar_int(tmp + '0', fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:45:35 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:54:26 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	int	tmp;

	if (nbr <= 9 && nbr >= 0)
		ft_putchar_fd((nbr + '0'), fd);
	else if (nbr == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((nbr * -1), fd);
	}
	else
	{
		tmp = nbr % 10;
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(tmp + '0', fd);
	}
}

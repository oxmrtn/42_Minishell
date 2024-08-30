/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:42:47 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:50:04 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int	ft_putchar_int(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_int(char *s, int fd)
{
	int		tot;
	size_t	len;

	if (!s)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	if (*s)
		write(fd, s, len);
	tot = (int) len;
	return (tot);
}

void	ft_putnbr_int(int nbr, int fd, int *tot)
{
	int	tmp;

	if (nbr <= 9 && nbr >= 0)
		*tot += ft_putchar_int((nbr + '0'), fd);
	else if (nbr == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*tot += 11;
	}
	else if (nbr < 0)
	{
		*tot += ft_putchar_int('-', fd);
		ft_putnbr_int((nbr * -1), fd, tot);
	}
	else
	{
		tmp = nbr % 10;
		ft_putnbr_int(nbr / 10, fd, tot);
		*tot += ft_putchar_int(tmp + '0', fd);
	}
}

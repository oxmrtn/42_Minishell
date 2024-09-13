/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:58:04 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:49:59 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int	print_type(va_list params, char c)
{
	int	printed;

	printed = 0;
	if (c == 'd')
		ft_putnbr_int(va_arg(params, int), 1, &printed);
	else if (c == 's')
		printed = ft_putstr_int(va_arg(params, char *), 1);
	else if (c == '%')
		printed = ft_putchar_int('%', 1);
	else if (c == 'c')
		printed = ft_putchar_int(va_arg(params, int), 1);
	else if (c == 'X')
		ft_putnbr_base(va_arg(params, int), "0123456789ABCDEF", &printed);
	else if (c == 'x')
		ft_putnbr_base(va_arg(params, int), "0123456789abcdef", &printed);
	else if (c == 'i')
		ft_putnbr_int(va_arg(params, int), 1, &printed);
	else if (c == 'u')
		ft_putnbr_unsigned(va_arg(params, unsigned int), 1, &printed);
	else if (c == 'p')
		ft_getaddress(va_arg(params, void *), &printed);
	return (printed);
}

int	ft_printf(const char *src, ...)
{
	va_list	parametersstatus;
	int		i;
	int		j;

	va_start(parametersstatus, src);
	i = -1;
	j = 0;
	if (!src)
		return (-1);
	while (src[++i] && src)
	{
		if (src[i] != '%')
			j += ft_putchar_int(src[i], 1);
		else if (src[i + 1] && ft_strchr("cspdiuxX%", src[i + 1]))
		{
			j += print_type(parametersstatus, src[i + 1]);
			i++;
		}
		else
			return (va_end(parametersstatus), -1);
	}
	va_end(parametersstatus);
	return (j);
}

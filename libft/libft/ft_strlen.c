/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:15:02 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 16:43:08 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (i);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_custom_len(char *src)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		if (src[i] != 34 && src[i] != 39)
			len++;
		i++;
	}
	return (len);
}

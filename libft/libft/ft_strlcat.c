/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:22:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dest && size == 0)
		return (0);
	len = ft_strlen(dest);
	i = 0;
	j = 0;
	while (dest[j] && j < size)
		j++;
	if (size > 0)
	{
		while (src[i] && j < size - 1)
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	if (size > len)
		dest[j] = '\0';
	return (ft_strlen(src) + min (size, len));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:25:13 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				len;
	char				*str;
	const unsigned char	c_char = (unsigned char)c;

	len = ft_strlen(s);
	str = (char *)s;
	while (len > 0)
	{
		if (str[len] == c_char)
			return (&(str[len]));
		len--;
	}
	if (c_char == str[len])
		return (&(str[len]));
	return (NULL);
}

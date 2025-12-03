/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:06:03 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int		i;
	const unsigned char	c_char = (unsigned char)c;
	char				*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == c_char)
			return (&(str[i]));
		i++;
	}
	if (str[i] == '\0' && c_char == '\0')
		return (&(str[i]));
	return (NULL);
}

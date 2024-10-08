/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:09:36 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	char	*c;
	size_t	i;
	size_t	j;

	j = 0;
	c = (char *)s;
	i = ft_strlen(c);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = (f)(j, s[j]);
		j++;
	}
	result[j] = '\0';
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:45:34 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/28 14:19:18 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;
	size_t	k;

	k = start;
	if (len < (ft_strlen(s) - k))
		size = len;
	else
		size = ft_strlen(s) - k;
	if (ft_strlen(s) <= k)
		return (NULL);
	result = malloc((sizeof(char) * (size + 1)));
	if (!result || !s)
	{
		return (NULL);
	}
	ft_strlcpy(result, s + k, size + 1);
	return (result);
}

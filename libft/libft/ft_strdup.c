/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:42:12 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/17 16:41:59 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(char *src)
{
	char	*result;
	size_t	i;

	i = ft_strlen(src);
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(result, src, i + 1);
	return (result);
}

char	*ft_strdup_till_i(char *src, int i)
{
	char	*result;

	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, src, i + 1);
	return (result);
}

char	*ft_strdup_custom(char *src)
{
	char	*result;
	size_t	i;
	int		k;

	i = ft_custom_len(src);
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (src[i])
	{
		if (src[i] != 34 && src[i] != 39)
		{
			result[k] = src[i];
			k++;
		}
		i++;
	}
	result[k] = '\0';
	return (result);
}

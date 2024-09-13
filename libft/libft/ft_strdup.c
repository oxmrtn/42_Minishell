/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:42:12 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 16:39:34 by mtrullar         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:20:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/06/24 10:53:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	j;
	size_t	i;
	char	*result;

	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	if (i >= ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[j]))
		j--;
	result = malloc(sizeof(char) * (j - i + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &(s1[i]), (j - i + 2));
	return (result);
}

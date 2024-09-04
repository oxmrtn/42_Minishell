/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:15:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/03 14:39:10 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (free(s1), ft_strdup(s1));
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1, len_s1 + 1);
		ft_strlcpy(result + len_s1, s2, len_s1 + len_s2 + 1);
	}
	return (result);
}

char	*ft_strjoin_s1(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (free(s1), ft_strdup(s1));
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1, len_s1 + 1);
		ft_strlcpy(result + len_s1, s2, len_s1 + len_s2 + 1);
	}
	free(s1);
	return (result);
}

char	*ft_strjoin_s2(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (free(s1), ft_strdup(s1));
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
		if (!result)
			return (NULL);
		ft_strlcpy(result, s1, len_s1 + 1);
		ft_strlcpy(result + len_s1, s2, len_s1 + len_s2 + 1);
	}
	free(s2);
	return (result);
}

char	*ft_strjoin_c(char *s1, char *s2, char c, int sfree)
{
	size_t	len1;
	size_t	len2;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len1);
	dst[len1] = c;
	ft_strlcpy(&dst[len1 + 1], s2, len2);
	if (sfree == 1)
		free(s1);
	if (sfree == 2)
		free(s2);
	return (dst);
}

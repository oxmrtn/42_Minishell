/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:30:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/18 14:30:35 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			diff = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (diff);
		}
		i++;
	}
	return (0);
}

int	ft_ultimate_compare(char *s1, char *s2)
{
	unsigned int		i;
	int					diff;
	size_t				len_s1;
	size_t				len_s2;
	unsigned int		n;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	n = ft_max((int)len_s1, (int)len_s2);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			diff = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (diff);
		}
		i++;
	}
	return (0);
}

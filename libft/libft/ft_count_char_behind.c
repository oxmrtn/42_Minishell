/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char_behind.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:50:54 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 15:16:25 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

// Return the number of charset equal to c behind str[i]
int	ft_count_char_behind(char *str, int i, char c)
{
	int	j;

	j = i;
	while (j >= 0 && str[j] && str[j] == c)
		j--;
	return (i - j);
}

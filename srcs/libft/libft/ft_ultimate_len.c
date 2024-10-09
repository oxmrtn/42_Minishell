/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:53:31 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/10 11:24:15 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ultimate_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
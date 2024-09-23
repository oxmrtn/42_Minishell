/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:46:55 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/23 10:42:42 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_cd(t_data *data, char **cmdve)
{
	(void)data;
	if (cmdve[1] && cmdve[2])
		return (ft_puterror("minishell error: cd too many arguments\n"), 1);
	return (0);
}

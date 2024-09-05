/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:45:11 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/05 16:14:41 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_echo(t_data *data, char **cmdve)
{
	(void)data;
	printf("builtin: %s\n", cmdve[0]);
	return (0);
}

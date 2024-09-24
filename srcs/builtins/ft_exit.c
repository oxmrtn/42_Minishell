/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:42 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/24 14:22:32 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_exit(t_data *data, char **cmdve)
{
	int	exit_code;

	if (ft_ultimate_len(cmdve) > 2)
		return (ft_puterror("minishell error: too many argument for exit\n"), 1);
	if (cmdve[1])
		exit_code = ft_atoi(cmdve[1]);
	else
		exit_code = data->exit_status;
	free_main(data);
	exit(exit_code % 256);
}

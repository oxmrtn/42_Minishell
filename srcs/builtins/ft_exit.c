/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:42 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/03 15:35:27 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	does_i_exit(t_data *data)
{
	t_tokens	*node;

	node = ft_get_last_commands(data->cmds)->tokens;
	while (node)
	{
		if (node->type == PIPE)
			return (1);
		node = node->next;
	}
	return (0);
}

static int	alpha_in_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			if ((str[i] != '+' && str[i] != '-') || i > 0)
				return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_data *data, char **cmdve)
{
	long long	exit_code;

	if (does_i_exit(data))
		return (1);
	if (ft_ultimate_len(cmdve) > 2 && !alpha_in_args(cmdve[1]))
		return (ft_puterror("minishell error: too many argument for exit\n")
			, 1);
	if (cmdve[1])
	{
		exit_code = ft_atoll(cmdve[1]);
		if (alpha_in_args(cmdve[1]) || exit_code > 9223372036854775807
			|| exit_code <= (-9223372036854775807))
		{
			ft_puterror("minishell error: exit numeric argument required\n");
			exit_code = 2;
		}
	}
	else
		exit_code = data->exit_status;
	free_main(data, 1);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_code % 256);
	return (1);
}

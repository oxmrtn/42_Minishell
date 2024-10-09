/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:48:42 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/09 17:07:19 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	is_validval(char *str)
{
	int				fn;
	const size_t	len_nbr = ft_strlen("9223372036854775808");
	size_t			len;
	int				temp;

	fn = 0;
	if (str && str[0] == '-')
	{
		str = str + 1;
		fn = 1;
	}
	len = ft_strlen(str);
	if (len > len_nbr)
		return (0);
	if (len < len_nbr)
		return (1);
	temp = ft_strncmp(str, "9223372036854775808", len);
	if (fn == 1)
		temp = ft_strncmp(str, "9223372036854775809", len);
	if (temp >= 0)
		return (0);
	else
		return (1);
}

static int	is_numstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			&& ((!i && str[i] != '-' && str[i] != '+') || i > 0))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data, char **cmdve)
{
	long long	exit_code;
	int			is_valid;

	exit_code = ((is_valid = 0));
	if (cmdve[1])
		if (is_numstr(cmdve[1]) && is_validval(cmdve[1]))
			is_valid = 1;
	if (cmdve[1] && !is_valid)
	{
		ft_desc_error("exit", "numeric argument required", 0, NULL);
		exit_code = 2;
	}
	if (is_valid && cmdve[1] && cmdve[2])
		return (ft_desc_error("exit", "too many arguments", 0, NULL), 1);
	if (cmdve[1] && is_valid)
		exit_code = ft_atoll(cmdve[1]);
	if (!cmdve[1])
		exit_code = data->exit_status;
	if (data->cmdvesize > 1)
		return (exit_code);
	write(STDOUT_FILENO, "exit\n", 5);
	free_main(data, 1);
	exit(exit_code % 256);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/15 20:50:04 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		retval;

	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, env))
		return (free_main(data, 0), 1);
	retval = 0;
	while (1)
	{
		retval = the_loop(data);
		if (retval == 1)
			ft_puterror("minishell: internal error\n");
		if (retval == 0 || retval == 1)
			break ;
	}
	if (retval != 1)
		retval = data->exit_status;
	free_main(data, 1);
	return (retval);
}

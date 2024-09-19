/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:18 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/19 14:58:17 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_pwd(void)
{
	char	*test;

	test = getcwd(0, 0);
	if (test)
	{
		if (write(STDOUT_FILENO, test, ft_strlen(test)) < 0)
		{
			ft_puterror("minishell error : cannot write in outfile\n");
			return (free(test), 1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:37:48 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/27 18:08:15 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_puterror(char *str)
{
	ft_putstr_fd(str, 2);
}

void	ft_desc_error(char *cmd, char *wrong, int order)
{
	ft_puterror("minishell: ");
	if (!order)
	{
		ft_puterror("'");
		ft_puterror(cmd);
		ft_puterror("': ");
		ft_puterror(wrong);
	}
	else
	{
		ft_puterror(cmd);
		ft_puterror(": '");
		ft_puterror(wrong);
		ft_puterror("': ");
	}
}

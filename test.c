/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:55:32 by ebengtss          #+#    #+#             */
/*   Updated: 2024/09/27 14:03:48 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

int main(void)
{
    struct stat blbl;

    stat(".mini", &blbl);
    if (S_ISDIR(blbl.st_mode))
        printf("dir\n");
    else
        printf("not\n");
    return (0);
}

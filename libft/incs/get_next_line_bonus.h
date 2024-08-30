/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:53:47 by mtrullar          #+#    #+#             */
/*   Updated: 2024/07/03 11:43:14 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct gn_list
{
	char			content;
	struct gn_list	*next;
}				t_gnl_list;

t_gnl_list	*ft_new_node(char buffer);
t_gnl_list	*ft_lst_last(t_gnl_list *node);

int			ft_line_in_lst(t_gnl_list **node, t_gnl_list **to_del);

char		*ft_lst_to_buffer(t_gnl_list **node, t_gnl_list **to_del);
char		*get_next_line(int fd);

void		ft_lst_add_back(t_gnl_list *new_node, t_gnl_list **current_node);
void		ft_del_lst(t_gnl_list **node, t_gnl_list **to_del);
void		buffer_to_lst(t_gnl_list **node, char *buffer);

#endif
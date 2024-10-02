/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:42:12 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/02 19:15:54 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(char *src)
{
	char	*result;
	size_t	i;

	i = ft_strlen(src);
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(result, src, i + 1);
	return (result);
}

char	*ft_strdup_till_i(char *src, int i)
{
	char	*result;

	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, src, i + 1);
	return (result);
}

static void	bis(char *str, int i, t_nk *check)
{
	if (str[i] == 34 && check->i == 1)
		check->i = 0;
	else if (str[i] == 34 && check->i == 0)
		check->i = 1;
	else if (str[i] == 39 && check->i == 2)
		check->i = 0;
	else if (str[i] == 39 && check->i == 0)
		check->i = 2;
	else if (str[i] == 92 && check->j == 0)
		check->j = 1;
	else if (str[i] == 92 && check->j == 1)
		check->j = 0;
	else if (str[i] == ' ' && str[i - 1] && str[i - 1] != ' ')
		check->k = 0;
	else if (str[i] == ' ' && str[i - 1] && str[i - 1] == ' ')
		check->k = 1;
}

static int	ft_len(char *src)
{
	int		i;
	int		k;
	t_nk	c;

	c.i = 0;
	c.j = 0;
	c.k = 0;
	k = 0;
	i = 0;
	while (src[i])
	{
		bis(src, i, &c);
		if ((src[i] == 34 && c.i == 2) || (src[i] == 39 && c.i == 1)
			|| (src[i] == ' ' && c.k == 0)
			|| (src[i] != 34 && src[i] != 39 && src[i] != ' '))
			k++;
		i++;
	}
	return (k);
}

char	*ft_strdup_custom(char *src)
{
	char	*result;
	int		i;
	int		k;
	t_nk	c;

	c.i = 0;
	c.j = 0;
	c.k = 0;
	i = ft_len(src);
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (src[i])
	{
		bis(src, i, &c);
		if ((src[i] == 34 && c.i == 2) || (src[i] == 39 && c.i == 1)
			|| (src[i] == ' ' && c.k == 0)
			|| (src[i] != 34 && src[i] != 39 && src[i] != ' '))
			result[k++] = src[i];
		i++;
	}
	result[k] = '\0';
	return (result);
}

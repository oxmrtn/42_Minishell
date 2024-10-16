/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:03:25 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/16 18:27:01 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_free_split(char **strs)
{
	size_t	i;

	i = 0;
	if (strs && *strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}

int	cpt_words(char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && i >= 0 && !(i >= 1 && str[i - 1] == c))
			words++;
		i++;
	}
	if (!(str[0]))
		return (0);
	if (str[i - 1] != c)
		return (words + 1);
	return (words);
}

static char	**free_all(char **buffer, int buffer_index)
{
	while (buffer_index >= 0)
	{
		free(buffer[buffer_index]);
		buffer_index--;
	}
	free(buffer);
	return (NULL);
}

static char	**split_bis(char **buffer, char *str, char c)
{
	int	i;
	int	j;
	int	buffer_index;

	i = 0;
	j = 0;
	buffer_index = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == '\0' || str[i + 1] == c))
		{
			buffer[buffer_index] = malloc(sizeof(char) * (i - j + 2));
			if (!buffer[buffer_index])
				return (free_all(buffer, buffer_index));
			ft_strlcpy(buffer[buffer_index], &str[j], (i - j + 2));
			buffer_index++;
		}
		if (str[i++] == c && str[i] != c)
			j = i;
	}
	buffer[buffer_index] = 0;
	return (buffer);
}

char	**ft_split(char *str, char c)
{
	char	**buffer;
	int		size;

	size = cpt_words(str, c);
	if (size == 0)
		return (NULL);
	buffer = malloc(sizeof(char *) * (size + 1));
	if (buffer == NULL)
		return (NULL);
	if (size == 0)
	{
		buffer[0] = NULL;
		return (buffer);
	}
	split_bis(buffer, str, c);
	return (buffer);
}

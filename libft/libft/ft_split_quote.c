/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:00:31 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/11 17:24:15 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static void	*ft_free_all(char **strs, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	ft_count_word(char const *str, char set)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (str[i + 1] && str[i + 1] != 39)
			{
				if (!str[i - 1])
				{
					counter++;
				}
				else
				{
					if (str[i - 1] == set)
						counter++;
				}
			}
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		else if (str[i] && str[i] == 34)
		{
			if (!str[i - 1])
			{
				counter++;
			}
			else
			{
				if (str[i - 1] == set)
					counter++;
			}
			i++;
			while (str[i] && str[i] != 34)
				i++;
		}
		else if (i == 0 && str[i] && str[i] != set)
			counter++;
		else if (str[i] && str[i] == set && str[i + 1] != '\0'
			&& (str[i + 1] != set && str[i + 1] != 34 && str[i + 1] != 39))
			counter++;
		i++;
	}
	return (counter);
}

static void	ft_split_init(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

static int	ft_run_split(char **splitted_str, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	ft_split_init(&i, &j, &k);
	while (s[i])
	{
		if (s[i] == 34)
		{
			j = i + 1;
			while (s[j] && s[j] != 34)
			{
				j++;
			}
			splitted_str[k] = malloc(sizeof(char) * (j - i + 2));
			if (!splitted_str[k])
				return (ft_free_all(splitted_str, k), 1);
			ft_strlcpy(splitted_str[k], &s[i], (j - i + 2));
			k++;
			i = j;
		}
		else if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			splitted_str[k] = malloc(sizeof(char) * (i - j + 2));
			if (!splitted_str[k])
				return (ft_free_all(splitted_str, k), 1);
			ft_strlcpy(splitted_str[k], &s[j], (i - j + 2));
			k++;
		}
		if (s[i++] == c && s[i] != c)
			j = i;
	}
	return (splitted_str[k] = NULL, 0);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**splitted_str;
	int		words;

	words = ft_count_word(s, c);
	printf(" ------------------WORDS-------%d \n\n", words);
	if (words == 0)
		return (NULL);
	splitted_str = malloc(sizeof(char *) * (words + 1));
	if (!splitted_str)
		return (NULL);
	if (ft_run_split(splitted_str, s, c))
		return (NULL);
	return (splitted_str);
}
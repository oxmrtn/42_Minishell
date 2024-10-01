/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:00:31 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 18:58:28 by mtrullar         ###   ########.fr       */
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
	int		check;

	check = 0;
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == 39 && check == 0)
			check = 1;
		else if (str[i] == 39 && check == 1)
			check = 0;
		else if (str[i] == 34 && check == 0)
			check = 2;
		else if (str[i] == 34 && check == 2)
			check = 0;
		if (i == 0 && str[i] != set)
			counter++;
		if (str[i] == set && str[i + 1]
			&& str[i + 1] != set && check == 0)
			counter++;
		i++;
	}
	return (counter);
}

static void	ft_split_init(t_nk *p)
{
	p->check = 0;
	p->i = 0;
	p->j = 0;
	p->k = 0;
}

static int	ft_run_split(char **splitted_str, char const *s, char c)
{
	t_nk	p;

	ft_split_init(&p);
	while (s[p.i])
	{
		if (s[p.i] == 39 && p.check == 0)
			p.check = 1;
		else if (s[p.i] == 39 && p.check == 1)
			p.check = 0;
		if (s[p.i] == 34 && p.check == 0)
			p.check = 2;
		else if (s[p.i] == 34 && p.check == 2)
			p.check = 0;
		if (s[p.i] != c && (s[p.i + 1] == '\0'
				|| s[p.i + 1] == c) && (p.check == 0 || !s[p.i + 1]))
		{
			splitted_str[p.k] = malloc(sizeof(char) * (p.i - p.j + 2));
			if (!splitted_str[p.k])
				return (ft_free_all(splitted_str, p.k), 1);
			ft_strlcpy(splitted_str[p.k++], &s[p.j], (p.i - p.j + 2));
		}
		if (s[p.i++] == c && s[p.i] != c && p.check == 0)
			p.j = p.i;
	}
	return (splitted_str[p.k] = NULL, 0);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**splitted_str;
	int		words;

	words = ft_count_word(s, c);
	if (words == 0)
		return (NULL);
	splitted_str = malloc(sizeof(char *) * (words + 1));
	if (!splitted_str)
		return (NULL);
	if (ft_run_split(splitted_str, s, c))
		return (NULL);
	return (splitted_str);
}

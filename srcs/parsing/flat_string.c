/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:45:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/14 23:50:56 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*ft_append(char *s1, char *str, int i, int check)
{
	char			*buffer;
	const size_t	len = ft_strlen(s1);

	if (str[i] == 92 && check != 2)
	{
		if ((ft_count_char_behind(str, i, 92) % 2 != 0))
			return (s1);
	}
	if (!s1)
	{
		buffer = malloc(sizeof(char) * 2);
		if (!buffer)
			return (NULL);
		buffer[0] = str[i];
		buffer[1] = '\0';
		return (buffer);
	}
	buffer = malloc(sizeof(char) * (len + 2));
	if (!buffer)
		return (s1);
	ft_strlcpy(buffer, s1, len + 1);
	buffer[len] = str[i];
	buffer[len + 1] = '\0';
	free(s1);
	return (buffer);
}

static int	ft_append_var_bis(char *str, int *flag)
{
	if (!str)
		return (1);
	if (ft_strchr(str, ' '))
	{
		if (flag)
			*flag = 1;
	}
	return (0);
}

static int	ft_append_var(char **s1, char *s2, t_data *data, int *flag)
{
	int		i;
	char	*key;
	char	*temp;

	temp = ((key = NULL));
	i = 0;
	while (s2[i] && (!(s2[i] >= 0 && s2[i] <= 47)
			&& !(s2[i] >= 58 && s2[i] <= 62)
			&& !(s2[i] >= 91 && s2[i] <= 94) && s2[i] != 96 && s2[i] != 64
			&& s2[i] != '\n' && !(s2[i] >= 123 && s2[i] <= 127))
		&& (s2[i] != '?' || (s2[i] == '?' && i == 0)))
		i++;
	if (i == 0)
		return (*s1 = ft_strjoin_s1(*s1, "$"), 0);
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (0);
	ft_strlcpy(key, s2, i + 1);
	temp = ft_get_variable_value(key, data);
	if (ft_append_var_bis(temp, flag))
		return (free(key), 0);
	*s1 = ft_strjoin_s1(*s1, temp);
	return (i = (int)ft_strlen(key), free(key), free(temp), i);
}

static void	flat_bis(char *str, int i, t_nk *check, t_tokens *current)
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
	else if (i >= 2 && str[i - 1] == '<' && str[i - 2] == '<')
		check->k = 1;
	else
		check->k = 0;
	if (i == 0 && (str[i] == 34 || str[i] == 39))
		if (current)
			current->expand = 3;
}

char	*ft_flat_string(char *str, t_data *data, int *flag, t_tokens *current)
{
	int		i;
	char	*buf;
	t_nk	check;

	if (ft_check_quote_syntax(str))
		return (NULL);
	i = -1;
	check.i = ((check.j = ((check.k = 0))));
	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	while (str[++i])
	{
		flat_bis(str, i, &check, current);
		if (str[i] == '$' && check.i != 2 && check.j != 1
			&& (check.k != 1 && check.i == 0 && check.j == 0))
			i += ft_append_var(&buf, &str[i + 1], data, flag);
		else
		{
			if ((check.i == 1 && str[i] == 39) || (check.i == 2 && str[i] == 34)
				|| (str[i] != 34 && str[i] != 39))
				buf = ft_append(buf, str, i, check.i);
		}
	}
	return (buf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:45:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 15:02:15 by mtrullar         ###   ########.fr       */
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

static void	ft_append_var_bis(int *i, char *key)
{
	if (key)
	{
		*i = (int)ft_strlen(key);
		free(key);
	}
	else
		*i = 1;
}

static int	ft_append_var(char **s1, char *s2, t_data *data)
{
	int		i;
	char	*key;
	char	*temp;

	temp = NULL;
	key = NULL;
	i = 0;
	while (s2[i] && s2[i] != ' ' && s2[i] != '\n' && s2[i] != 39 && s2[i] != 34
		&& s2[i] != '$' && s2[i] != ':')
		i++;
	if (i != 0)
	{
		key = malloc(sizeof(char) * (i + 1));
		if (!key)
			return (0);
		ft_strlcpy(key, s2, i + 1);
		temp = ft_get_variable_value(key, data);
	}
	else
		temp = ft_strdup("?");
	if (!temp)
		return (0);
	*s1 = ft_strjoin_s1(*s1, temp);
	ft_append_var_bis(&i, key);
	return (free(temp), i);
}

static void	flat_bis(char *str, int i, int *check)
{
	if (str[i] == 34 && *check == 1)
		*check = 0;
	else if (str[i] == 34 && *check == 0)
		*check = 1;
	else if (str[i] == 39 && *check == 2)
		*check = 0;
	else if (str[i] == 39 && *check == 0)
		*check = 2;
}

char	*ft_flat_string(char *str, t_data *data)
{
	int		i;
	char	*buf;
	int		check;

	if (ft_check_quote_syntax(str))
		return (NULL);
	i = -1;
	check = 0;
	buf = NULL;
	while (str[++i])
	{
		flat_bis(str, i, &check);
		if (str[i] == '$' && check != 2)
			i += ft_append_var(&buf, &str[i + 1], data);
		else
		{
			if ((check == 1 && str[i] == 39) || (check == 2 && str[i] == 34))
				buf = ft_append(buf, str, i, check);
			else if (str[i] != 34 && str[i] != 39)
				buf = ft_append(buf, str, i, check);
		}
	}
	return (buf);
}

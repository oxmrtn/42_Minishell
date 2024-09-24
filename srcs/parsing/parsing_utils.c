/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:45:56 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/24 17:46:48 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	ft_append_var(char **s1, char *s2, t_data *data)
{
	int		i;
	char	*key;
	char	*buff;
	char	*temp;

	i = 0;
	while (s2[i] && s2[i] != ' ' && s2[i] != '\n' && s2[i] != 39 && s2[i] != 34)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (0);
	ft_strlcpy(key, s2, i + 1);
	temp = ft_get_variable_value(key, data);
	buff = ft_strjoin_s1(*s1, temp);
	free(temp);
	i = (int)ft_strlen(key);
	free(key);
	*s1 = buff;
	return (i);
}

static char	*ft_append(char *s1, char c)
{
	char			*buffer;
	const size_t	len = ft_strlen(s1);

	if (!s1)
	{
		buffer = malloc(sizeof(char) * 2);
		if (!buffer)
			return (NULL);
		buffer[0] = c;
		buffer[1] = '\0';
		return (buffer);
	}
	buffer = malloc(sizeof(char) * (len + 2));
	if (!buffer)
		return (s1);
	ft_strlcpy(buffer, s1, len + 1);
	buffer[len] = c;
	buffer[len + 1] = '\0';
	free(s1);
	return (buffer);
}

static void	flat_bis(char *str, int i, int *check)
{
	if (str[i] == 34 && *check != 2)
		*check = 1;
	else if (str[i] == 34 && *check == 1)
		*check = 0;
	else if (str[i] == 39 && *check != 1)
		*check = 2;
	else if (str[i] == 39 && *check == 2)
		*check = 0;
}

char	*ft_flat_string(char *str, t_data *data)
{
	int		i;
	char	*buf;
	int		check;

	if (ft_check_quote_syntax(str))
		return (NULL);
	i = 0;
	check = 0;
	buf = NULL;
	while (str[i])
	{
		flat_bis(str, i, &check);
		if (str[i] == '$' && check != 2)
			i += ft_append_var(&buf, &str[i + 1], data);
		else
		{
			if ((check == 1 && str[i] == 39) || (check == 2 && str[i] == 34))
				buf = ft_append(buf, str[i]);
			else if (str[i] != 34 && str[i] != 39)
				buf = ft_append(buf, str[i]);
		}
		i++;
	}
	return (buf);
}

int	count_cmd(t_tokens *actu)
{
	int	result;

	result = 0;
	while (actu && ft_ultimate_compare(actu->str, "|"))
	{
		if (actu->type == CMD)
			result++;
		actu = actu->prev;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:28:34 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/15 18:19:32 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	handle_redir_bis(t_tokens *current, char c, int *i, char *str)
{
	char	tmp[3];

	if (c == '>')
		ft_strlcpy(tmp, ">>", 3);
	else if (c == '<')
		ft_strlcpy(tmp, "<<", 3);
	else
		ft_strlcpy(tmp, "||", 3);
	if (c == '>' || c == '<')
	{
		if ((*i) - 1 >= 0 && str[(*i) - 1] == c)
		{
			if (add_tokens_between((str + *i + 1), current, WAIT, 3)
				|| add_tokens_between(tmp, current, WAIT, 3))
				return (1);
			(*i)--;
		}
		else if (add_tokens_between((str + *i + 1), current, WAIT, 3)
			|| add_tokens_between((tmp + 1), current, WAIT, 3))
			return (1);
	}
	if (c == '|' && (add_tokens_between((str + *i + 1), current, WAIT, 3)
			|| add_tokens_between((tmp + 1), current, WAIT, 3)))
		return (1);
	return (0);
}

static int	change_value_node(t_tokens *current, char **str, int i)
{
	free(current->str);
	current->str = ft_strdup_till_i(*str, i);
	if (!current->str)
		return (1);
	if (((*str)[i]) == '\0')
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	*str += i;
	return (0);
}

static int	current_str(char **str, t_tokens *current)
{
	int		i;
	char	*src;

	src = *str;
	i = 0;
	while (src[i] && src[i] != '>' && src[i] != '<' && src[i] != '|')
		i++;
	if (i == 0)
	{
		if (src[1] && src[1] == src[0])
		{
			if (change_value_node(current, str, 2))
				return (1);
		}
		else
		{
			if (change_value_node(current, str, 1))
				return (1);
		}
	}
	else
		if (change_value_node(current, str, i))
			return (1);
	return (0);
}

static int	split_redir_loop(char *str, int i, t_tokens *current)
{
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
	{
		if (handle_redir_bis(current, str[i], &i, str))
			return (1);
		str[i] = '\0';
	}
	return (0);
}

int	split_redir(t_tokens *current)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strdup(current->str);
	if (!str)
		return (1);
	tmp = str;
	if (current_str(&str, current))
		return (1);
	if (!str)
		return (0);
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (split_redir_loop(str, i, current))
			return (free(tmp), 1);
		i--;
	}
	if (str[0] != '\0')
		if (add_tokens_between(str, current, WAIT, 3))
			return (1);
	return (free(tmp), 0);
}

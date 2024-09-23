/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/23 16:07:37 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	print_commands(t_cmds *com)
{
	t_cmds *commands = com;
	t_tokens *tokens;

	if (!commands)
		return (printf("NO COMMANDS\n"), 1);
	while (commands)
	{
		printf("Commands : |%s| \n", commands->cmd);
		printf("Tokens associated with this cmds : \n");
		tokens = commands->tokens;
		while (tokens)
		{
			printf("Tokens name = |%s| \n", tokens->str);
			printf("Tokens type = %d \n", tokens->type);
			tokens = tokens->next;
		}
		commands = commands->next;
	}
	return (0);
}

int	print_variable(t_data *data)
{
	t_var	*head;

	head = data->var;
	while (head)
	{
		printf("Variable  = |$%s| || Content = |%s|\n", head->name, head->content);
		head = head->next;
	}
	return (0);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		printf("minishell → ^C\nminishell → ");
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*read;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->exit_status = 0;
	data->var = NULL;
	data->stdincpy = dup(STDIN_FILENO);
	data->stdoutcpy = dup(STDOUT_FILENO);
	if (data->stdincpy == -1 || data->stdoutcpy == -1)
		return (1);
	signal(SIGINT, &handle_signal);
	(void)argc;
	(void)argv;
	if (!env[0])
		return (0);
	if (env_init(data, env))
		return (1);
	printf("Welcome to MINISHELL\n");
	data->cmds = NULL;
	data->cmdve = NULL;
	ft_get_history();
	ft_add_variable("?=0", data);
	while (1)
	{
		read = readline("minishell → ");
		add_history(read);
		ft_parser(read, &data->cmds, data);
		if (exec(data, ft_get_last_commands(data->cmds)))
			return (free_main(data), 1);
		char	*temp = ft_itoa(data->exit_status);
		ft_update_variable("?", temp, data);
		free(temp);
		free(read);
		read = NULL;
	}
	return (0);
}

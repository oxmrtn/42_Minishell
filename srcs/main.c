/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/05 13:45:09 by ebengtss         ###   ########.fr       */
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

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		printf("minishell → ^C\nminishell → ");
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*read;
	t_cmds	*commands;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->exit_status = 0;
	data->var = NULL;
	signal(SIGINT, &handle_signal);
	(void)argc;
	(void)argv;
	if (!env[0])
		return (0);
	if (make_env(data, env))
		return (1);
	printf("Welcome to MINISHELL\n");
	commands = NULL;
	data->cmdve = NULL;
	ft_get_history(&commands);
	while (1)
	{
		read = readline("minishell → ");
		add_history(read);
		if (!ft_strncmp(read, "exit", 4))
			return (ft_free_commands(commands), 0);
		ft_parser(read, &commands, data);
		print_commands(commands);
		if (exec(data, ft_get_last_commands(commands)))
			return (free_main(data), 1);
		free(read);
		read = NULL;
	}
	ft_write_history(commands);
	ft_free_commands(commands);
	return (0);
}

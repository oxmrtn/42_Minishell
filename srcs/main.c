/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/03 15:26:34 by ebengtss         ###   ########.fr       */
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
		printf("Commands : %s \n", commands->cmd);
		printf("Tokens associated with this cmds : \n");
		tokens = commands->tokens;
		while (tokens)
		{
			printf("Tokens name = %s \n", tokens->str);
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
	signal(SIGINT, &handle_signal);
	(void)argc;
	(void)argv;
	if (!env[0])
		return (0);
	if (make_env(data, env))
		return (1);
	printf("Welcome to MINISHELL\n");
	commands = NULL;
	ft_get_history(&commands);
	read = readline("minishell → ");
	while (read)
	{
		if (!ft_strncmp(read, "exit", 4))
			return (ft_free_commands(commands), 0);
		ft_parser(read, &commands);
		if (exec(data, commands))
			return (1);
		print_commands(commands);
		add_history(read);
		free(read);
		read = readline("minishell → ");
	}
	ft_write_history(commands);
	ft_free_commands(commands);
}

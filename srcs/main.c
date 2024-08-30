/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 18:34:54 by mtrullar         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*read;
	t_cmds	*commands;
	
	(void)argc;
	(void)argv;
	if (!env[0])
		return (0);
	printf("Welcome to MINISHELL\n");
	commands = NULL;
	ft_get_history(&commands);
	read = readline("minishell → ");
	while (read)
	{
		//printf("%s\n", read);
		ft_parser(read, &commands);
		print_commands(commands);
		free(read);
		read = readline("minishell → ");
	}
	ft_write_history(commands);
	ft_free_commands(commands);
}
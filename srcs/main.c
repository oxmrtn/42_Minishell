/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/01 14:29:42 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	print_commands(t_cmds *com)
{
	t_cmds		*commands;
	t_tokens	*tokens;

	commands = com;
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
		printf("Variable  = |$%s| || Content = |%s|\n",
			head->name, head->content);
		head = head->next;
	}
	return (0);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); 
	return ;
}

void	sig_handle(int signo)
{
	printf("\n\n\n%d\n\n\n", signo);
}

static int	init_data(t_data *data, char **env)
{
	data->exit_status = 0;
	data->var = NULL;
	data->read = NULL;
	data->tmpexitstatus = NULL;
	data->cmds = NULL;
	data->cmdve = NULL;
	data->stdincpy = dup(STDIN_FILENO);
	data->stdoutcpy = dup(STDOUT_FILENO);
	if (data->stdincpy == -1 || data->stdoutcpy == -1)
		return (1);
	if (ft_get_history())
		return (1);
	if (ft_add_variable("?=0", data))
		return (1);
	if (env_init(data, env))
		return (1);
	return (0);
}

static int	the_loop(t_data *data)
{
	data->read = readline("minishell$ ");
	if (!data->read)
		return (printf("exit\n"), 0);
	add_history(data->read);
	if (ft_parser(data->read, &data->cmds, data) == 0)
	{
		//print_commands(ft_get_last_commands(data->cmds));
		if (exec(data, ft_get_last_commands(data->cmds)))
			return (1);
	}
	data->tmpexitstatus = ft_itoa(data->exit_status);
	if (!data->tmpexitstatus)
		return (1);
	if (ft_update_variable("?", data->tmpexitstatus, data))
		return (1);
	free(data->tmpexitstatus);
	free(data->read);
	data->tmpexitstatus = NULL;
	return (2);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		retval;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data || init_data(data, env))
		return (1);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	retval = 0;
	while (1)
	{
		retval = the_loop(data);
		if (retval == 0 || retval == 1)
			break ;
	}
	free_main(data);
	return (retval);
}

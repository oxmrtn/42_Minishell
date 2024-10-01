/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/01 18:45:59 by mtrullar         ###   ########.fr       */
=======
/*   Updated: 2024/10/01 19:12:07 by ebengtss         ###   ########.fr       */
>>>>>>> ebengtss/exec
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	sig_status;

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

void	sig_handle(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		sig_status = 130;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		ft_putstr_fd("\33[2K\r", 1);
		rl_redisplay();
		sig_status = 131;
	}
}

static int	init_data(t_data *data, char **env)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = sig_handle;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sig_status = 0;
	data->exit_status = 0;
	data->var = NULL;
	data->read = NULL;
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

static int	update_status(t_data *data, int status)
{
	char	*tmp;

	tmp = ft_itoa(status);
	if (!tmp)
		return (1);
	if (ft_update_variable("?", tmp, data))
		return (1);
	free(tmp);
	return (0);
}

static int	the_loop(t_data *data)
{
	printf("\33[2K\r");
	data->read = readline("minishell$ ");
	if (!data->read)
		return (printf("exit\n"), 0);
	if (sig_status != 0)
		if (update_status(data, sig_status))
			return (1);
	if (!ft_ultimate_compare(data->read, "\0"))
		return (2);
	add_history(data->read);
	if (ft_parser(data->read, &data->cmds, data) == 0)
		if (exec(data, ft_get_last_commands(data->cmds)))
			return (1);
	if (update_status(data, data->exit_status))
		return (1);
	free(data->read);
	data->read = NULL;
	sig_status = 0;
	return (2);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		retval;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
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

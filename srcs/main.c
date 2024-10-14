/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:27:49 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/14 23:15:23 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_sig_status;



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
		g_sig_status = 130;
	}
	if (signo == SIGQUIT)
	{
		if (!isatty(STDIN_FILENO))
			ft_putstr_fd("Quit (core dumped)\n", 1);
		rl_on_new_line();
		ft_putstr_fd("\33[2K\r", 1);
		rl_redisplay();
		g_sig_status = 131;
	}
}

static int	init_data(t_data *data, char **env)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = sig_handle;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	g_sig_status = 0;
	data->exit_status = ((data->isrunned) = 0);
	data->cmdvesize = 0;
	data->isoutred = 0;
	data->var = NULL;
	data->read = NULL;
	data->cmds = NULL;
	data->cmdve = NULL;
	data->heredoc = NULL;
	data->hd_filler = NULL;
	data->stdincpy = dup(STDIN_FILENO);
	data->stdoutcpy = dup(STDOUT_FILENO);
	if (data->stdincpy == -1 || data->stdoutcpy == -1)
		return (1);
	if (ft_get_history() || ft_add_variable("?=0", data))
		return (1);
	if (env_init(data, env))
		return (1);
	return (0);
}

static int	update_status(t_data *data, int is_exec)
{
	char	*tmp;

	if (g_sig_status == 0 && !is_exec)
		return (0);
	if (g_sig_status != 0
		&& (!is_exec || (is_exec && !data->isrunned)))
		data->exit_status = g_sig_status;
	tmp = ft_itoa(data->exit_status);
	if (!tmp)
		return (1);
	if (ft_update_variable("?", tmp, data))
		return (1);
	free(tmp);
	g_sig_status = 0;
	return (0);
}

static int	the_loop(t_data *data)
{
	printf("\33[2K\r");
	data->read = readline("minishell$ ");
	if (update_status(data, 0))
	{
		if (data->read)
			free(data->read);
		return (data->read = NULL, 1);
	}
	if (!data->read)
		return (printf("exit\n"), 0);
	if (ft_iswhite(data->read))
		return (free(data->read), data->read = NULL, 2);
	data->isrunned = 0;
	add_history(data->read);
	if (ft_parser(data->read, &data->cmds, data) == 0)
	{
		print_commands(ft_get_last_commands(data->cmds));
		if (exec(data, ft_get_last_commands(data->cmds)))
			return (free(data->read), data->read = NULL, 1);
	}
	if (update_status(data, 1))
		return (free(data->read), data->read = NULL, 1);
	return (free(data->read), data->read = NULL, 2);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		retval;

	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, env))
		return (free_main(data, 0), 1);
	retval = 0;
	while (1)
	{
		retval = the_loop(data);
		if (retval == 0 || retval == 1)
			break ;
	}
	if (retval != 1)
		retval = data->exit_status;
	free_main(data, 1);
	return (retval);
}

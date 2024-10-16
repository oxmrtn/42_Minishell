/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:43:33 by ebengtss          #+#    #+#             */
/*   Updated: 2024/10/16 18:03:21 by mtrullar         ###   ########.fr       */
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

void	sig_handle_hd(int signo)
{
	if (signo == SIGINT)
	{
		g_sig_status = 140;
		ft_putstr_fd("\n", 1);
		close(STDIN_FILENO);
	}
	if (signo == SIGQUIT)
	{
		g_sig_status = 131;
		ft_putstr_fd("\33[2K\r", 1);
		(rl_on_new_line(), rl_redisplay());
	}
}

void	sig_handle(int signo)
{
	if (signo == SIGINT)
	{
		g_sig_status = 130;
		rl_replace_line("\0", 0);
		ft_putstr_fd("\n", 1);
		(rl_on_new_line(), rl_redisplay());
		if (!isatty(STDIN_FILENO))
			ft_putstr_fd("\33[2K\r", 1);
	}
	if (signo == SIGQUIT)
	{
		g_sig_status = 131;
		if (!isatty(STDIN_FILENO))
		{
			rl_replace_line("\0", 0);
			ft_putstr_fd("Quit (core dumped)\n", 1);
			(rl_on_new_line(), rl_redisplay());
			ft_putstr_fd("\33[2K\r", 1);
			return ;
		}
		ft_putstr_fd("\33[2K\r", 1);
		(rl_on_new_line(), rl_redisplay());
	}
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

int	init_data(t_data *data, char **env)
{
	ft_bzero(&data->saction, sizeof(data->saction));
	data->saction.sa_handler = sig_handle;
	sigaction(SIGINT, &data->saction, NULL);
	sigaction(SIGQUIT, &data->saction, NULL);
	signal(SIGTSTP, SIG_IGN);
	g_sig_status = 0;
	data->sstatus = &g_sig_status;
	data->exit_status = ((data->isrunned) = 0);
	data->cmdvesize = ((data->isoutred) = 0);
	data->tmpstdin = -1;
	data->tmppwd = NULL;
	data->var = NULL;
	data->read = NULL;
	data->cmds = NULL;
	data->cmdve = NULL;
	data->heredoc = ((data->hd_filler) = NULL);
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

int	the_loop(t_data *data)
{
	int	rev;

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
	rev = ft_parser(data->read, &data->cmds, data);
	if (rev == 1)
		return (free(data->read), data->read = NULL, 1);
	if (rev == 0)
		if (exec(data, ft_get_last_commands(data->cmds)))
			return (free(data->read), data->read = NULL, 1);
	if (update_status(data, 1))
		return (free(data->read), data->read = NULL, 1);
	return (free(data->read), data->read = NULL, 2);
}

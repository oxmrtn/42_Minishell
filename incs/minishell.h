/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/03 15:38:18 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	NO_TYPE,
	CMD,
	ARGS,
	INFILE,
	LIMITER,
	OUTFILE,
	APPEND
}	t_type;

typedef struct s_tokens
{
	char			*str;
	t_type			type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}					t_tokens;

typedef struct s_cmds
{
	char			*cmd;
	t_tokens		*tokens;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

//	Parsing
int			ft_parser(char *line, t_cmds **commands);
t_tokens	*create_token_list(char *line);
int			add_new_token(char *str, t_tokens **head, int i);
t_tokens	*ft_get_last_token(t_tokens *head);
t_type		get_type(char *str, int i);
int			add_commands(t_cmds *new, t_cmds **head);
t_cmds		*ft_get_last_commands(t_cmds *tmp);

//	History
int			ft_get_history(t_cmds **cmds);
int			ft_write_history(t_cmds *cmds);

//	Free
void		ft_free_tokens(t_tokens *tok);
void		ft_free_commands(t_cmds *cmds);

typedef struct s_data
{
	t_cmds	*cmds;
	t_env	*env;
	int		exit_status;
}			t_data;

/* EXEC */
int		exec(t_data *data, t_cmds *cmd);
int		is_inred(t_cmds *cmd, int *i, char ***cmdve);
int		is_outred(t_cmds *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_data *data, char **cmdve);
int		run_cmd(char **cmdve, t_data *data, t_cmds *cmd, int islast);
int		run_heredoc(char *limiter);
int		cmds_path(char ***cmdve, t_data *data);


/* BUILTINS */
int		ft_echo(t_data *data, t_cmds *cmd);
int		ft_cd(t_data *data, t_cmds *cmd);
int		ft_pwd(t_data *data, t_cmds *cmd);
int		ft_export(t_data *data, t_cmds *cmd);
int		ft_unset(t_data *data, t_cmds *cmd);
int		ft_env(t_data *data, t_cmds *cmd);
int		ft_exit(t_data *data, t_cmds *cmd);


/* ENV */
int		make_env(t_data	*data, char **env);


#endif
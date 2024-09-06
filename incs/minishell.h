/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/06 18:41:47 by mtrullar         ###   ########.fr       */
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
	WAIT,		//0
	NO_TYPE,	//1
	CMD,		//2
	ARGS,		//3
	PIPE,		//4
	INFILE,		//5
	LIMITER,	//6
	OUTFILE,	//7
	APPEND,		//8
	REDIR,		//9
	ERROR,		//10
	ASK			//11
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

typedef struct s_var
{
	char	*name;
	char	*content;
	struct s_var	*next;
	struct s_var	*prev;
}			t_var;

typedef struct s_data
{
	t_cmds	*cmds;
	t_env	*env;
	t_var	*var;
	char	***cmdve;
	int		exit_status;
}			t_data;

//	PARSING
//		parsing.c
int			ft_parser(char *line, t_cmds **commands, t_data *data);

//		commands_struct.c
t_cmds		*ft_get_last_commands(t_cmds *tmp);
int			add_commands(t_cmds *new, t_cmds **head);

//		handle_variable.c
int		ft_add_variable(char *str, t_data *data);
int		ft_is_variable_declaration(char *str);

//		here_docs.c
void	ft_heredoc_handler(t_tokens *head);

//		tokenization.c
int		ft_is_pipe(t_tokens *current);
int		ft_is_redirect_sign(t_tokens *current);
int		ft_is_args(t_tokens *node);
int		ft_is_commands(t_tokens *node);

//		tokens_struct.c
t_tokens	*ft_get_last_token(t_tokens *head);
t_tokens	*create_token_list(char *line);
int			add_new_token(char *str, t_tokens **head);
void		get_type(t_tokens *head_node);

//		var_list_func.c
t_var		*ft_last_var(t_var *head);
void		ft_var_add_back(t_var *new_node, t_var *head);


//	HISTORY
int			ft_get_history();
int			ft_write_history(t_cmds *cmds);

//	FREE
//		conditionnal_free.c
void		free_invalid_syntax(t_cmds *to_free);

//		free.c
void		free_main(t_data *data);
void		ft_free_tokens(t_tokens *tok);
void		ft_free_commands(t_cmds *cmds);
void		ft_free_env(t_env *env);
void		ft_free_cmdve(char ***cmdve);

/* EXEC */
int		exec(t_data *data, t_cmds *cmd);
int		is_inred(t_cmds *cmd, int *i, char ***cmdve);
int		is_outred(t_cmds *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_data *data, char **cmdve);
int		run_cmd(char **cmdve, t_data *data, t_cmds *cmd, int islast);
int		run_heredoc(char *limiter);
int		reset_fds(void);
void	cleanup_exec(char ***cmdve);


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
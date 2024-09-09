/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/09 17:34:57 by ebengtss         ###   ########.fr       */
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
	WAIT,
	NO_TYPE,
	CMD,
	ARGS,
	PIPE,
	INFILE,
	LIMITER,
	OUTFILE,
	APPEND,
	ERROR
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

typedef struct s_env
{
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_envs
{
	t_env	*env;
	t_env	*l_env;
	t_env	*exp;
	t_env	*l_exp;
}			t_envs;

typedef struct s_data
{
	t_cmds	*cmds;
	t_envs	*envs;
	t_var	*var;
	char	***cmdve;
	int		exit_status;
}			t_data;

//	Parsing
int			ft_parser(char *line, t_cmds **commands, t_data *data);
t_tokens	*create_token_list(char *line, t_data *data);
int			add_new_token(char *str, t_tokens **head);
t_tokens	*ft_get_last_token(t_tokens *head);
void		get_type(t_tokens *head_node, t_data *data);
int			add_commands(t_cmds *new, t_cmds **head);
t_cmds		*ft_get_last_commands(t_cmds *tmp);

//	VAR FUNC

int		ft_is_variable_declaration(char *str);
int		ft_add_variable(char *str, t_data *data);
//	VAR LIST UTILS

t_var		*ft_last_var(t_var *head);
void		ft_var_add_back(t_var *new_node, t_var *head);


//	History
int			ft_get_history(t_cmds **cmds);
int			ft_write_history(t_cmds *cmds);

//	Free
void		free_main(t_data *data);
void		ft_free_cmdve(char ***cmdve);
void		ft_free_tokens(t_tokens *tok);
void		ft_free_commands(t_cmds *cmds);


/* EXEC */
int		exec(t_data *data, t_cmds *cmd);
int		is_inred(t_cmds *cmd, int *i, char ***cmdve);
int		is_outred(t_cmds *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_data *data, char **cmdve);
int		run_cmd(t_data *data, int i, t_cmds *cmd, int islast);
int		run_heredoc(char *limiter);
int		exec_exit(t_data *data, int status);
char	***ft_make_cmdve(t_cmds *cmd);
int		ft_fill_cmdve(char ***cmdve, t_cmds *cmd);
int		cmds_path(char ***cmdve, t_data *data);


/* BUILTINS */
int		ft_echo(t_data *data, char **cmdve);
int		ft_cd(t_data *data, char **cmdve);
int		ft_pwd(t_data *data, char **cmdve);
int		ft_export(t_data *data, char **cmdve);
int		ft_unset(t_data *data, char **cmdve);
int		ft_env(t_data *data, char **cmdve);
int		ft_exit(t_data *data, char **cmdve);


/* ENV */
int		env_init(t_data	*data, char **env);
t_env	*ft_envnew(char *str);
void	ft_envadd_front(t_env **lst, t_env *new);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);
void	ft_envdelone(t_data *data, t_env *node, int which);
void	print_env(t_env *env);


#endif
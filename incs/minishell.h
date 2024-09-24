/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/24 13:47:47 by ebengtss         ###   ########.fr       */
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
	ASK,		//11
	ENV
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
	char			*name;
	char			*content;
	struct s_var	*next;
	struct s_var	*prev;
}			t_var;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				exp_noval;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_envs
{
	t_env	*env;
	t_env	*exp;
	t_env	*l_env;
	char	**tmpenv;
	char	**envve;
}			t_envs;

typedef struct s_data
{
	t_cmds	*cmds;
	t_envs	*envs;
	t_var	*var;
	char	***cmdve;
	int		exit_status;
	int		stdincpy;
	int		stdoutcpy;
}			t_data;

//	PARSING
//		parsing.c
int			ft_parser(char *line, t_cmds **commands, t_data *data);
int			print_commands(t_cmds *com);

//		check_error.c
int			ft_check_quote_syntax(char *str);

//		commands_struct.c
t_cmds		*ft_get_last_commands(t_cmds *tmp);
int			add_commands(t_cmds *new, t_cmds **head);

//		handle_variable.c
int			ft_add_variable(char *str, t_data *data);
int			ft_check_variable(char *str, t_data *data);
char		*ft_get_variable_value(char *key, t_data *data);
void		ft_update_variable(char *key, char *val, t_data *data);

//		here_docs.c
void		ft_heredoc_handler(t_tokens *head, t_data *data);
void		ft_ask_handler(t_tokens *head, t_data *data);

//		tokenization.c
int			ft_is_pipe(t_tokens *current);
int			ft_is_redirect_sign(t_tokens *current);
int			ft_is_args(t_tokens *node);
int			ft_is_commands(t_tokens *node);

//		tokens_struct.c
t_tokens	*ft_get_last_token(t_tokens *head);
t_tokens	*create_token_list(char *line, t_data *data);
int			add_new_token(char *str, t_tokens **head, t_type type);
void		get_type(t_tokens *head_node);

//		var_list_func.c
t_var		*ft_last_var(t_var *head);
t_var		*ft_is_var_exist(char *str, t_var *head, int i);
void		ft_var_add_back(t_var *new_node, t_var **head);

//		parsing_utils.c
char		*ft_flat_string(char *str, t_data *data);
int			count_cmd(t_tokens *actu);

//	HISTORY
int			ft_get_history(void);
int			ft_write_history(t_cmds *cmds);

//	FREE
//		conditionnal_free.c
void		ft_free_invalid_syntax(t_cmds *to_free);

//		free.c
void		free_main(t_data *data);
void		ft_free_cmdve(char ***cmdve);
void		ft_free_tokens(t_tokens *tok);
void		ft_free_commands(t_cmds *cmds);
void		ft_free_env(t_env **lst);
void		ft_free_cmdve(char ***cmdve);

/* EXEC */
int			exec(t_data *data, t_cmds *cmd);
int			is_inred(t_cmds *cmd, int *i);
int			is_outred(t_cmds *cmd, int i);
t_tokens	*skip_tokens(t_cmds *cmd, int i);
int			is_builtin(char *cmd);
int			exec_builtin(t_data *data, char **cmdve);
int			run_gtw(t_data *data, t_cmds *cmd, int *i, int islast);
char		***ft_make_cmdve(t_cmds *cmd, int *j);
int			ft_fill_cmdve(char ***cmdve, t_cmds *cmd);
int			cmds_path(char ***cmdve, t_data *data, int j);
int			reset_fds(t_data *data, int std);

/* BUILTINS */
int		ft_echo(char **cmdve);
int		ft_cd(t_data *data, char **cmdve);
int		ft_pwd(t_data *data);
int		ft_export(t_data *data, char **cmdve);
int		env_update(t_env *lst, char *str);
int		ft_unset(t_data *data, char **cmdve);
int		ft_env(t_data *data, char **cmdve);
int		ft_exit(t_data *data, char **cmdve);

/* ENV */
t_env		*envnew_gtw(char *str, int is_exp_no_val);
size_t		ft_envsize(t_env *lst);
int			env_init(t_data	*data, char **env);
t_env		*ft_envnew(char *key, char *val, int is_exp_no_val);
void		ft_envadd_front(t_env **lst, t_env *new);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*ft_envlast(t_env *lst);
void		ft_envdelone(t_data *data, t_env *node);
char		**env_to_tab(t_data *data);
void		print_env(t_env *env, int env_or_exp);
int			env_update(t_env *lst, char *str);
int			tmp_env_add(t_data *data, char *cmdve);
void		tmp_env_clean(t_data *data);
int			tmp_env_setup(t_data *data, t_cmds *cmd, int i);
int			env_update(t_env *lst, char *str);

#endif
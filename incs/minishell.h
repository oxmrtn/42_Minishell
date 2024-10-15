/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/15 19:59:50 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

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
	REDIR,
	ERROR,
	ASK,
	ENV
}	t_type;

typedef struct s_hd
{
	int			fd;
	struct s_hd	*next;
	struct s_hd	*prev;
}				t_hd;

typedef struct s_tokens
{
	char			*str;
	t_type			type;
	int				expand;
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
}					t_var;

typedef struct s_env
{
	int				hidden;
	char			*key;
	char			*val;
	int				exp_noval;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_envs
{
	int		direrr;
	t_env	*env;
	t_env	*exp;
	t_env	*tmpenv;
	t_env	*l_env;
	char	**tmpenvve;
	char	**envve;
}			t_envs;

typedef struct s_data
{
	struct sigaction	saction;
	int					sstatus;
	t_cmds				*cmds;
	t_envs				*envs;
	t_var				*var;
	t_hd				*heredoc;
	t_hd				*hd_filler;
	char				***cmdve;
	char				*read;
	char				*tmppwd;
	int					exit_status;
	int					stdincpy;
	int					stdoutcpy;
	int					isoutred;
	int					cmdvesize;
	int					iheredoc;
	int					isrunned;
}						t_data;

//	PARSING

//		check_error.c
int			ft_cqs(char *str);

//		commands_struct.c
t_cmds		*ft_get_last_commands(t_cmds *tmp);
int			add_commands(t_cmds *new, t_cmds **head);

//		flat_strings.c
char		*ft_flat_string(char *str, t_data *data, int *flag, t_tokens *c);
char		*ft_append(char *s1, char *str, int i, int check);

//		flat_strings_bis.c
int			flat_string_cond_1(int res, int *i);
int			flat_string_cond_2(char **buf, char *str, int i, t_nk check);
int			flat_string_init(t_nk *check, char **buf);

//		get_type.c
int			get_type(t_tokens *head, t_data *data);

//		handle_variable.c
int			ft_add_variable(char *str, t_data *data);
int			ft_check_variable(char *str, t_data *data);
char		*ft_get_variable_value(char *key, t_data *data);
int			ft_update_variable(char *key, char *val, t_data *data);

//		hd_list.c
t_hd		*ft_last_hd(t_hd *head);
void		add_back_heredoc_list(t_hd *new_node, t_hd **head);
int			add_heredoc_list(int fd, t_data *data);
void		del_top_hd(t_data *data);

//		here_docs.c
int			ft_heredoc_handler(t_tokens *head, t_data *data);
int			ft_ask_handler(t_tokens *head, t_data *data);

//		parsing.c
int			ft_parser(char *line, t_cmds **commands, t_data *data);
int			print_commands(t_cmds *com);

//		split_redir.c
int			split_redir(t_tokens *current);

//		tokenization_utils.c
int			ft_is_redirect_sign(t_tokens *current);

//		tokenization.c
int			ft_is_commands(t_tokens *node);
int			ft_is_args(t_tokens *node);

//		tokens_struct.c
int			add_tokens_between(char *str, t_tokens *current, t_type t, int i);
t_tokens	*create_token_list(char *line, t_data *data);

//		utils.c
void		ft_fix(t_tokens *head, char **splitted);
int			ft_is_pipe(t_tokens *current);
int			add_new_token(char *str, t_tokens **head, t_type type, int flag);
t_tokens	*ft_get_last_token(t_tokens *head);
int			count_cmd(t_tokens *actu);

//		var_list_func.c
t_var		*ft_last_var(t_var *head);
void		ft_var_add_back(t_var *new_node, t_var **head);
t_var		*ft_is_var_exist(char *str, t_var *head, int i);

//	HISTORY
int			ft_get_history(void);
int			ft_write_history(t_cmds *cmds);

//	FREES

//		free.c
void		ft_free_heredoc(t_data *data);
void		ft_free_cmdve(t_data *data);
void		ft_free_env(t_env **lst);
void		ft_free_envs(t_data *data);
void		free_main(t_data *data, int i);

//		free2.c
void		ft_free_tokens(t_tokens *tok);
void		ft_free_commands(t_cmds *cmds);
void		ft_free_invalid_syntax(t_cmds *to_free);
void		ft_free_var(t_data *data);

/* EXEC */
int			exec(t_data *data, t_cmds *cmd);
int			run_cmd(t_data *data, int i, int islast);
int			is_redirs(t_data *data, t_cmds *cmd, int i);
t_tokens	*skip_tokens(t_cmds *cmd, int i);
int			is_builtin(char *cmd);
int			exec_builtin(t_data *data, char **cmdve);
int			run_gtw(t_data *data, t_cmds *cmd, int *i, int islast);
char		***ft_make_cmdve(t_data *data, t_cmds *cmd);
int			fill_cmdve(char ***cmdve, t_cmds *cmd);
int			cmds_path(char ***cmdve, t_data *data);
int			reset_fds(t_data *data, int std);

/* BUILTINS */
int			ft_echo(char **cmdve);
int			echo_option_check(char *option);
int			ft_cd(t_data *data, char **cmdve);
int			update_old_pwd(t_data *data, char *oldpwd);
int			cd_handle_flag(t_data *data);
int			ft_pwd(t_data *data);
int			ft_export(t_data *data, char **cmdve);
int			ft_unset(t_data *data, char **cmdve);
int			ft_env(t_data *data, char **cmdve);
int			ft_exit(t_data *data, char **cmdve);

/* ENV */
char		*env_getval_key(t_env *lst, char *key);
int			env_update_keyval(t_env *lst, char *key, char *newval);
int			expenv_add2(t_data *data, char *cmdve, int env_or_exp);
int			set_path(t_data *data);
int			add_min_env(t_data *data, char *defkey, char *defval, int is_exp);
t_env		*envnew_gtw(char *str, int is_exp_no_val);
size_t		ft_envsize(t_env *lst);
int			env_init(t_data	*data, char **env);
t_env		*ft_envnew(char *key, char *val, int is_exp_no_val);
void		ft_envadd_front(t_env **lst, t_env *new);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*ft_envlast(t_env *lst);
int			ft_envdup(t_data *data);
int			incr_shlvl(t_data *data);
int			envtab_update(t_data *data);
int			is_inenv_key(t_env *env, char *keycheck);
int			is_inenv_str(t_env *env, char *strcheck);
void		ft_envdelone(t_data *data, t_env *node);
char		**env_to_tab(t_env *env);
int			print_env(t_env *env);
int			print_exp(t_env *env);
int			tmp_env_add(t_data *data, char *cmdve);
int			tmp_env_setup(t_data *data, t_cmds *cmd, int i);
int			env_update(t_env *lst, char *str);
int			check_env(t_data *data);
int			isvalid_env(char *str, int only_key);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/02 13:53:19 by ebengtss         ###   ########.fr       */
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
	REDIR_IN,
	REDIR_IN_PATH
}	t_type;

typedef struct s_tokens
{
	char			*str;
	t_type			*type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}					t_tokens;

typedef struct s_cmds
{
	char			*cmd;
	t_tokens		*tokens;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmds;

typedef struct s_data
{
	t_cmds	*cmds;
	t_env	*env;
}			t_data;

/* EXEC */
int	exec(t_data *data, t_cmds *cmd);
int	ft_echo(t_data *data, t_cmds *cmd);
int	ft_cd(t_data *data, t_cmds *cmd);
int	ft_pwd(t_data *data, t_cmds *cmd);
int	ft_export(t_data *data, t_cmds *cmd);
int	ft_unset(t_data *data, t_cmds *cmd);
int	ft_env(t_data *data, t_cmds *cmd);
int	ft_exit(t_data *data, t_cmds *cmd);

/* UTILS */

#endif
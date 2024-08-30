/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 15:47:52 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

<<<<<<< HEAD
typedef enum type_token
{
    NO_TYPE,
    CMD,
    ARGS,
    REDIR_IN,
    REDIR_IN_PATH
};

typedef struct tokens
{
    char *str;
    enum type_token type;
    struct tokens *next;
    struct tokens *prev;
}				t_tokens;

typedef struct cmd
{
    char *cmd;
    struct tokens tokens;
    struct cmd *next;
    struct cmd *prev;
}				t_cmd;
=======
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
	t_type			type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}					t_tokens;

typedef struct s_cmds
{
	char			*cmd;
	t_tokens		tokens;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmds;
>>>>>>> a7ba8724f65494a3982888559b172af9bef3897c

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:28:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/30 15:51:30 by mtrullar         ###   ########.fr       */
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

typedef enum type_token
{
    NO_TYPE,
    CMD,
    ARGS,
    REDIR_IN,
    REDIR_IN_PATH
}				t_type;

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

#endif
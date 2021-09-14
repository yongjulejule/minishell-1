/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:48 by ghan              #+#    #+#             */
/*   Updated: 2021/09/13 08:58:17 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* SECTION - include .h files */

# define READLINE_LIBRARY 1
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* SECTION - structs */

/* SECTION - function declarations */
char	**complete_a_line(char *ln_read);
int		exec_cmd_main(char **cmds, char **envp);
#endif

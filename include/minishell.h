/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:48 by ghan              #+#    #+#             */
/*   Updated: 2021/09/25 17:55:19 by ghan             ###   ########.fr       */
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
# include "libft.h"
# include "parse.h"
# include <readline/readline.h>
# include <readline/history.h>

/* function declarations */

/* utils_main */

t_cmds	*parse_line_main(char *ln_read);
int		exec_cmd_main(t_cmds *cmds, char **envp);
void	unexp_eof_sig_handler(void);
void	eof_exit(char *line_read);

/* main_signal */

void	main_sig_handler(int signal);
void	sigint_n_sigquit_handler(void (*sigfunction));
void	unexp_eof_sigint_handler(int sig);

#endif

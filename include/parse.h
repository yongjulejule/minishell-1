/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:11:55 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 01:54:13 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* Include Libraries */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

/*User Defines*/

typedef struct	s_cmds
{
	char			*cmd;
	struct s_cmds	*next;
}	t_cmds;

/* FUNCTIONS */

/* from_main */
void	free_cmds(char **cmds);
void	main_sig_handler(int signal);

/* internal prompt */
int		read_internal_prompt(char **one_ln, char *ln_read, int read_cnt);

/* utils_main */

char	*strchr_skip_bslash(const char *s, int c);
void	is_qmbt(char *one_ln, char **qmbt);
int		end_by_pipe(char *one_ln);
int		end_by_esc(char **one_ln);

/* split */

void	skip_normal_bslash(char *s, int *i);
void	skip_qmbt(char *str, int *i);
void	split_by_symbols(t_cmds **cmds_hd, char *s);
int		check_end_esc(char *str, char *charset);
char	**alloc_mem(char **tmp, char *start_addr, int len, int idx);

/* sub_env & syntax check */

void	sub_env(char **one_ln);
int		check_smcol_pipe_syntax(char **cmds);

/* split rdr */

void	get_rdr_end_idx(char *s, int *i);
int		check_valid_rdr_symbols(char *s, int i);

/* parse lst */

int		ps_lst_size(t_cmds *cmd);
t_cmds	*ps_lst_init(char *cmd);
t_cmds	*ps_lstlast(t_cmds *elem);
void	ps_lst_addback(t_cmds **hd, t_cmds *new);

#endif

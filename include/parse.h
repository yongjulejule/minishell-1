/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:11:55 by ghan              #+#    #+#             */
/*   Updated: 2021/09/12 17:11:57 by ghan             ###   ########.fr       */
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

/* FUNCTIONS */

/* from_main */
void	free_cmds(char **cmds);
void	main_sig_handler(int signal);

/* utils_main */

char	*strchr_skip_bslash(const char *s, int c);
void	is_qmbt(char *one_ln, char **qmbt);
int		end_by_pipe(char *one_ln);
int		end_by_esc(char **one_ln);

/* split */

void	skip_normal_bslash(char *s, int *i);
void	skip_qmbt(char *str, int *i);
char	**split_by_pipe_sc(char const *s, char *charset);
int		check_end_esc(char *str, char *charset);
char	**alloc_mem(char **tmp, char *start_addr, int len, int idx);

/* sub_env & syntax check */

void	sub_env(char **one_ln);
int		check_smcol_pipe_syntax(char **cmds);

/* split rdr */
void	check_rdr_size(char *s, int *size, int *i);
void	get_rdr_end_idx(char *s, int start, int *i, int n_cnt);
int		cnt_valid_rdr_symbols(char *s, int *i);

#endif
